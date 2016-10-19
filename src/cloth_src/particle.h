#include "../../utils/Vector3D.h"

class Particle {
private:
	Vector3D pos;
	Vector3D prev_pos;
	Vector3D accel;
	Vector3D normal;
	float mass;
	bool fixed;

public:
	Particle();
	Particle(Vector3D pos);
	void timeStep();
	void applyForce(Vector3D f);
	void offsetPos(const Vector3D offset);
	void addNorm(Vector3D normal);
	void makeFixed();
	void resetAccel();
	void resetNorm();
	bool isFixed();
	float getMass();
	Vector3D& getPos();
	Vector3D& getPrevPos();
	Vector3D& getAccel();
	Vector3D& getNormal();
};