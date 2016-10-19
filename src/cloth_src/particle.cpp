#include "particle.h"
#include "../params.h"

Particle::Particle() {
	pos = Vector3D();
	prev_pos = Vector3D();
	accel = Vector3D();
	normal = Vector3D();
	mass = 1.;
	fixed = false;
}

Particle::Particle(Vector3D position) {
	pos = position;
	prev_pos = position;
	accel = Vector3D();
	normal = Vector3D();
	mass = 1.;
	fixed = false;
}

void Particle::timeStep() {
	if (!fixed) {
		Vector3D temp = pos;
		pos = pos + (pos-prev_pos) * (1.0-DAMPING) + accel * TIMESTEP_SIZE;
		prev_pos = temp;
		resetAccel();
	}
}

void Particle::applyForce(Vector3D f) {
	accel += f / mass;
}

void Particle::offsetPos(const Vector3D offset) {
	if (!fixed) {
		pos += offset;
	}
}

void Particle::addNorm(Vector3D n) {
	normal += n.norm();
}

void Particle::makeFixed() {
	fixed = true;
}

void Particle::resetAccel() {
	accel = Vector3D();
}

void Particle::resetNorm() {
	normal = Vector3D();
}

bool Particle::isFixed() {
	return fixed;
}

float Particle::getMass() {
	return mass;
}

Vector3D& Particle::getPos() {
	return pos;
}

Vector3D& Particle::getPrevPos() {
	return prev_pos;
}

Vector3D& Particle::getAccel() {
	return accel;
}

Vector3D& Particle::getNormal() { 
	return normal;
}
