#include "spring.h"

Spring::Spring(Particle *particle0, Particle *particle1) {
	p0 = particle0;
	p1 = particle1;
	orig_length = (p0->getPos() - p1->getPos()).length();
}

void Spring::update() {
	float curr_dist = (p1->getPos() - p0->getPos()).length();
	Vector3D updateVec = (p1->getPos() - p0->getPos()) * (1 - orig_length/curr_dist);
	p0->offsetPos(updateVec / 2); 
	p1->offsetPos(-updateVec / 2); 
}