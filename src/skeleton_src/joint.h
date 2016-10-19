#ifndef JOINT_H
#define JOINT_H
#include <string>
#include <map>
#include <vector>
#include "dof.h"
#include "../../utils/Vector3D.h"
#include "jointTraverse.h"
#include "bone.h"

using namespace std;

class Joint {
public:
    
    Joint(const string& name, Bone* node) { 
        label = name;
        bone = node;
    }

    string getLabel() const { 
        return label; 
    }

    Bone* getBone() const { 
        return bone; 
    }

    DOF* getRotationAngle() const { 
        return (DOF*) &rDeg; 
    }

    Vector3D* getRotationAxis() const { 
        return (Vector3D*) &rAxis; 
    }

    Vector3D* getTranslation() const { 
        return (Vector3D*) &translation;
    }

    void setRotationAngle(const DOF& d) { 
        rDeg = d; 
    }

    void setRotationAxis(double x, double y, double z) { 
        rAxis.val[0] = x;
        rAxis.val[1] = y; 
        rAxis.val[2] = z;
    }

    void setTranslation(double x, double y, double z) { 
        translation.val[0] = x; 
        translation.val[1] = y; 
        translation.val[2] = z;
    }

private:
    string label;
    DOF rDeg;
    Vector3D rAxis;
    Vector3D translation;
    Bone* bone;
};

#endif