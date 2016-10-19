#include "cloth.h"
#include "params.h"

Particle* Cloth::getParticle(int x, int y) {
	return &particles[y*particleNum_x + x];
}

void Cloth::connectParticles(Particle *p1, Particle *p2) {
	springs.push_back(Spring(p1,p2));
}

Vector3D Cloth::calcTriNorm(Particle *p1,Particle *p2,Particle *p3) {
	Vector3D pos1 = p1->getPos();
	Vector3D pos2 = p2->getPos();
	Vector3D pos3 = p3->getPos();
	Vector3D v1 = pos2-pos1;
	Vector3D v2 = pos3-pos1;
	return v1.cross(v2);
}

void Cloth::applyForceTri(Particle *p1,Particle *p2,Particle *p3, const Vector3D direction) {
	Vector3D normal = calcTriNorm(p1,p2,p3);
	Vector3D d = normal.norm();
	Vector3D force = normal * (d.dot(direction));
	p1->applyForce(force);
	p2->applyForce(force);
	p3->applyForce(force);
}

void Cloth::drawTri(Particle *p1, Particle *p2, Particle *p3, const Vector3D color) {
	glColor3fv( (GLfloat*) &color );
	Vector3D a = p1->getNormal().norm();
	glNormal3fv((GLfloat *) &a);
	glVertex3fv((GLfloat *) &(p1->getPos()));
	Vector3D b = p2->getNormal().norm();
	glNormal3fv((GLfloat *) &(b));
	glVertex3fv((GLfloat *) &(p2->getPos()));
	Vector3D c = p3->getNormal().norm();
	glNormal3fv((GLfloat *) &(c));
	glVertex3fv((GLfloat *) &(p3->getPos()));
}

Cloth::Cloth(float width, float height, int particleNum_x, int particleNum_y) : particleNum_x(particleNum_x), particleNum_y(particleNum_y) {
	particles.resize(particleNum_x * particleNum_y);
	for(int x = 0; x < particleNum_x; x++) {
		for(int y = 0; y < particleNum_y; y++) {
			Vector3D pos = Vector3D(width * (x / (float) particleNum_x), -height * (y / (float) particleNum_y), 0);
			particles[y*particleNum_x + x]= Particle(pos);
		}
	}
	for(int x = 0; x < particleNum_x; x++) {
		for(int y = 0; y < particleNum_y; y++) {
			if (x < particleNum_x-1) {
				connectParticles(getParticle(x, y), getParticle(x+1, y));
			}
			if (y < particleNum_y-1) {
				connectParticles(getParticle(x, y), getParticle(x, y+1));
			}
			if (x < particleNum_x-1 && y < particleNum_y-1) {
				connectParticles(getParticle(x, y), getParticle(x+1, y+1));
			}
			if (x < particleNum_x-1 && y < particleNum_y-1) {
				connectParticles(getParticle(x+1, y), getParticle(x, y+1));
			}
		}
	}
	for(int x = 0; x < particleNum_x; x++) {
		for(int y = 0; y < particleNum_y; y++) {
			if (x < particleNum_x-2) {
				connectParticles(getParticle(x, y),getParticle(x+2, y));
			}
			if (y < particleNum_y-2) {
				connectParticles(getParticle(x, y),getParticle(x, y+2));
			}
			if (x < particleNum_x-2 && y < particleNum_y-2) {
				connectParticles(getParticle(x, y),getParticle(x+2, y+2));
			}
			if (x < particleNum_x-2 && y < particleNum_y-2) {
				connectParticles(getParticle(x+2, y),getParticle(x, y+2));	
			}
		}
	}
	for(int i = 0; i < particleNum_x; i++) {
		getParticle(i ,0)->makeFixed(); 
	}
}

void Cloth::draw() {
	std::vector<Particle>::iterator particle;
	for(particle = particles.begin(); particle != particles.end(); particle++) {
		(*particle).resetNorm();
	}
	for(int x = 0; x < particleNum_x-1; x++) {
		for(int y = 0; y < particleNum_y-1; y++) {
			Vector3D normal = calcTriNorm(getParticle(x+1, y),getParticle(x, y),getParticle(x, y+1));
			getParticle(x+1, y)->addNorm(normal);
			getParticle(x, y)->addNorm(normal);
			getParticle(x, y+1)->addNorm(normal);
			normal = calcTriNorm(getParticle(x+1, y+1),getParticle(x+1, y),getParticle(x, y+1));
			getParticle(x+1, y+1)->addNorm(normal);
			getParticle(x+1, y)->addNorm(normal);
			getParticle(x, y+1)->addNorm(normal);
		}
	}
	glBegin(GL_TRIANGLES);
	for(int x = 0; x < particleNum_x-1; x++) {
		for(int y = 0; y < particleNum_y-1; y++) {
			Vector3D color(0,0,0);
			color = Vector3D(1.0f, .0f, .0f);
			drawTri(getParticle(x+1, y), getParticle(x, y), getParticle(x, y+1), color);
			drawTri(getParticle(x+1, y+1), getParticle(x+1, y), getParticle(x, y+1), color);
		}
	}
	glEnd();
}

void Cloth::timeStep() {
	std::vector<Spring>::iterator s;
	for(int i=0; i<SPRING_ITERATIONS; i++) {
		for(s = springs.begin(); s != springs.end(); s++) {
			(*s).update();
		}
	}
	std::vector<Particle>::iterator particle;
	for(particle = particles.begin(); particle != particles.end(); particle++) {
		(*particle).timeStep();
	}
}

void Cloth::applyForce(const Vector3D direction) {
	std::vector<Particle>::iterator particle;
	for(particle = particles.begin(); particle != particles.end(); particle++) {
		(*particle).applyForce(direction);
	}
}

void Cloth::applyWindForce(const Vector3D direction) {
	for(int x = 0; x < particleNum_x-1; x++) {
		for(int y=0; y < particleNum_y-1; y++) {
			applyForceTri(getParticle(x+1, y), getParticle(x, y), getParticle(x, y+1), direction);
			applyForceTri(getParticle(x+1, y+1), getParticle(x+1, y), getParticle(x, y+1), direction);
		}
	}
}

void Cloth::updateCollision(const Vector3D center,const float radius ) {
	std::vector<Particle>::iterator particle;
	for(particle = particles.begin(); particle != particles.end(); particle++) {
		Vector3D v = (*particle).getPos()-center;
		float l = v.length();
		if (v.length() < radius) {
			(*particle).offsetPos(v.norm()*(radius-l));
		}
	}
}
