#ifndef JOINTTRAVERSE_H
#define JOINTTRAVERSE_H
#include "../skeleton.h"

class Joint;

class JointTraverse {
public:
	virtual void operator()(Joint* j) = 0;
};

#endif