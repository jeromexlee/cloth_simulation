#ifndef ANIMATION_H
#define ANIMATION_H

#include <map>
#include <string>
#include "skeleton.h"
#include "fowardkinematics.h"

using namespace std;

class FowardKinematics;
class Animation {
public:
    Animation(Skeleton* s, FowardKinematics* f);

    class Initializer : public JointTraverse {
    public:
        map<string, DOF> angles;
        Initializer(map<string, DOF> a) {angles = a;}
        virtual void operator()(Joint* j) {
            angles.insert(make_pair(j->getLabel(), *j->getRotationAngle()));
        }
    };

    class Updater : public JointTraverse {
    public:
        map<string, DOF> angles;
        Updater(map<string, DOF> a) {angles = a;}
        virtual void operator()(Joint* j) {
            map<string, DOF>::const_iterator iter = angles.find(j->getLabel());
            if(iter != angles.end()) {
                j->setRotationAngle(iter->second);
            }
        }
    };

    void update();
    void draw();
    Skeleton* skeleton;
    FowardKinematics* framer;
    map<string, DOF> angles;
};
#endif
