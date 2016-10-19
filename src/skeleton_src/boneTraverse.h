#ifndef BONETRAVERSE_H
#define BONETRAVERSE_H
#include "../skeleton.h"

class Bone;

class BoneTraverse {
public:
	virtual void operator()(Bone* node) = 0;
};

#endif