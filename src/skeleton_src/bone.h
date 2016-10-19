#ifndef BONE_H
#define BONE_H
#include <string>
#include <map>
#include <vector>
#include "dof.h"
#include "../../utils/Vector3D.h"
#include "jointTraverse.h"
#include "boneTraverse.h"
#include "joint.h"

using namespace std;

class Joint;

class Bone {
public:
    
    Bone(const string& l = "Link", Cube* cube = NULL) { 
        c = cube; 
        label = l;
    }

    string getLabel() const { 
        return label;
    }

    Cube* getCube() const { 
        return c;
    }

    void appendJoint(Joint* j) { 
        joints.push_back(j);
    }

    vector<Joint*>::iterator begin() { 
        return joints.begin(); 
    }

    vector<Joint*>::iterator end() { 
        return joints.end(); 
    }

private:
    string label;
    Cube* c;
    vector<Joint*> joints;
};
#endif