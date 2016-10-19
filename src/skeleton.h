#ifndef SKELETON_H
#define SKELETON_H
#include <vector>
#include <string>
#include <map>

#include "../utils/Vector3D.h"
#include "skeleton_src/jointTraverse.h"
#include "skeleton_src/boneTraverse.h"
#include "../utils/cube.h"
#include "params.h"
#include "skeleton_src/dof.h"
#include "skeleton_src/joint.h"
#include "skeleton_src/bone.h"

using namespace std;

class Skeleton {
public:
    Joint* root;

    Skeleton(Joint* r = NULL) {
        root = r;
        buildSkeleton();
        initializeAngles();
    }

    void traverseJoints(JointTraverse& visitor) {
        traverseJoint(root, visitor);
    }

    void update() const { 
        if (root) {
            updateJoint(root);
        } 
    }

    class AngleInitializer : public JointTraverse {
    public:
    map<string, DOF> angles;
    virtual void operator()(Joint* j) {
        map<string, DOF>::const_iterator iter = angles.find(j->getLabel());
        if(iter != angles.end())
            j->setRotationAngle(iter->second);
        }
    };

private:
    void initializeAngles();
    void buildSkeleton();
    void traverseJoint(Joint* j, JointTraverse& visitor);
    void updateJoint(const Joint* j) const;
};

#endif
