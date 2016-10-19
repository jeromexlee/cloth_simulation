#include "particle.h"

class Spring {
private:
	float orig_length;
public:
	Particle *p0;
	Particle *p1;
	Spring(Particle *p0, Particle *p1);
	void update();
};