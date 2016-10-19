#include <math.h>
#include <vector>
#include "OpenGL/gl.h"
#include "cloth_src/spring.h"

using namespace std;

class Cloth {
public:
	Cloth(float width, float height, int particleNum_x, int particleNum_y);
	void draw();
	void timeStep();
	Particle* getParticle(int x, int y);
	void connectParticles(Particle *p1, Particle *p2);
	void applyForce(const Vector3D direction);
	void applyWindForce(const Vector3D direction);
	void updateCollision(const Vector3D center, const float radius);
private:
	int particleNum_x;
	int particleNum_y;
	vector<Particle> particles;
	vector<Spring> springs;
	Vector3D calcTriNorm(Particle *p1,Particle *p2,Particle *p3);
	void applyForceTri(Particle *p1,Particle *p2,Particle *p3, const Vector3D direction);
	void drawTri(Particle *p1, Particle *p2, Particle *p3, const Vector3D color);
};