#include "OpenGL/gl.h"

#include "../utils/matrix44.h"
#include "skeleton.h"

using namespace std;

void Skeleton::initializeAngles() {
    AngleInitializer ai;
    ai.angles.insert(make_pair("root", DOF(0.0, 0.0, 0.0)));
    ai.angles.insert(make_pair("neck", DOF(0.0, -90.0, 90.0)));
    ai.angles.insert(make_pair("head", DOF(0.0, -45.0, 45.0)));
    ai.angles.insert(make_pair("shoulder_rz", DOF(0.0, 0.0, 90.0)));
    ai.angles.insert(make_pair("shoulder_ry", DOF(0.0, -90.0, 90.0)));
    ai.angles.insert(make_pair("shoulder_rx", DOF(0.0, -90.0, 90.0)));
    ai.angles.insert(make_pair("elbow_r", DOF(0.0, 0.0, 90.0)));
    ai.angles.insert(make_pair("shoulder_lz", DOF(0.0, 0.0, 90.0)));
    ai.angles.insert(make_pair("shoulder_ly", DOF(0.0, -90.0, 90.0)));
    ai.angles.insert(make_pair("shoulder_lx", DOF(0.0, -90.0, 90.0)));
    ai.angles.insert(make_pair("elbow_l", DOF(0.0, 0.0, 90.0)));
    ai.angles.insert(make_pair("hip_rz", DOF(0.0, -90.0, 90.0)));
    ai.angles.insert(make_pair("hip_ry", DOF(0.0, -90.0, 90.0)));
    ai.angles.insert(make_pair("hip_rx", DOF(10.0, -90.0, 90.0)));
    ai.angles.insert(make_pair("knee_r", DOF(-10.0, -120.0, 0.0)));
    ai.angles.insert(make_pair("ankle_r", DOF(0.0, -45.0, 45.0)));
    ai.angles.insert(make_pair("hip_lz", DOF(0.0, -90.0, 90.0)));
    ai.angles.insert(make_pair("hip_ly", DOF(0.0, -90.0, 90.0)));
    ai.angles.insert(make_pair("hip_lx", DOF(10.0, -90.0, 90.0)));
    ai.angles.insert(make_pair("knee_l", DOF(-10.0, -120.0, 0.0)));
    ai.angles.insert(make_pair("ankle_l", DOF(0.0, -45.0, 45.0)));
    traverseJoints(ai);
}

void Skeleton::buildSkeleton() {
    Cube* cube = new Cube();
    cube->setScale(0.25, 0.5, 0.10);
    Bone* torso = new Bone("body", cube);
    Joint* root_joint = new Joint("root", torso);
    root_joint->setTranslation(0.0, 0.5, 0.0);
    root = root_joint;
    cube = new Cube();
    cube->setScale(0.05, 0.05, 0.05);
    cube->setTranslation(0.0, 0.05, 0.0);
    Bone* neck = new Bone("neck", cube);
    Joint* neckBase = new Joint("neck", neck);
    neckBase->setTranslation(0.0, 0.5, 0.0);
    neckBase->setRotationAxis(0.0, 1.0, 0.0);
    torso->appendJoint(neckBase);
    cube = new Cube();
    cube->setScale(0.3, 0.3, 0.2);
    cube->setTranslation(0.0, 0.3, 0.0);
    Bone* head = new Bone("head", cube);
    Joint* headBase = new Joint("head", head);
    headBase->setTranslation(0.0, 0.05, 0.0);
    headBase->setRotationAxis(-1.0, 0.0, 0.0);
    neck->appendJoint(headBase);
    cube = new Cube();
    cube->setScale(0.0, 0.0, 0.0);
    Bone* rupperarmx = new Bone("uparm_rx", cube);
    Joint* rshoulderx = new Joint("shoulder_rx", rupperarmx);
    rshoulderx->setTranslation(-0.3, 0.5, 0.0);
    rshoulderx->setRotationAxis(-1.0, 0.0, 0.0);
    torso->appendJoint(rshoulderx);
    cube = new Cube();
    cube->setScale(0.0, 0.0, 0.0);
    Bone* rupperarmy = new Bone("uparm_ry", cube);
    Joint* rshouldery = new Joint("shoulder_ry", rupperarmy);
    rshouldery->setRotationAxis(0.0, -1.0, 0.0);
    rupperarmx->appendJoint(rshouldery);
    cube = new Cube();
    cube->setScale(0.05, 0.25, 0.05);
    cube->setTranslation(0.0, -0.25, 0.0);
    Bone* rupperarmz = new Bone("uparm_rz", cube);
    Joint* rshoulderz = new Joint("shoulder_rz", rupperarmz);
    rshoulderz->setRotationAxis(0.0, 0.0, -1.0);
    rupperarmy->appendJoint(rshoulderz);
    cube = new Cube();
    cube->setScale(0.05, 0.3, 0.05);
    cube->setTranslation(0.0, -0.3, 0.0);
    Bone* rlowerarm = new Bone("lowarm_r", cube);
    Joint* relbow = new Joint("elbow_r", rlowerarm);
    relbow->setTranslation(0.0, -0.5, 0.0);
    relbow->setRotationAxis(-1.0, 0.0, 0.0);
    rupperarmz->appendJoint(relbow);
    cube = new Cube();
    cube->setScale(0.0, 0.0, 0.0);
    Bone* lupperarmx = new Bone("uparm_lx", cube);
    Joint* lshoulderx = new Joint("shoulder_lx", lupperarmx);
    lshoulderx->setTranslation(0.3, 0.5, 0.0);
    lshoulderx->setRotationAxis(-1.0, 0.0, 0.0);
    torso->appendJoint(lshoulderx);
    cube = new Cube();
    cube->setScale(0.0, 0.0, 0.0);
    Bone* lupperarmy = new Bone("uparm_ly", cube);
    Joint* lshouldery = new Joint("shoulder_ly", lupperarmy);
    lshouldery->setRotationAxis(0.0, -1.0, 0.0);
    lupperarmx->appendJoint(lshouldery);
    cube = new Cube();
    cube->setScale(0.05, 0.25, 0.05);
    cube->setTranslation(0.0, -0.25, 0.0);
    Bone* lupperarmz = new Bone("uparm_lz", cube);
    Joint* lshoulderz = new Joint("shoulder_lz", lupperarmz);
    lshoulderz->setRotationAxis(0.0, 0.0, -1.0);
    lupperarmy->appendJoint(lshoulderz);
    cube = new Cube();
    cube->setScale(0.05, 0.30, 0.05);
    cube->setTranslation(0.0, -0.30, 0.0);
    Bone* llowerarm = new Bone("lowarm_l", cube);
    Joint* lelbow = new Joint("elbow_l", llowerarm);
    lelbow->setTranslation(0.0, -0.5, 0.0);
    lelbow->setRotationAxis(-1.0, 0.0, 0.0);
    lupperarmz->appendJoint(lelbow);
    cube = new Cube();
    cube->setScale(0.0, 0.0, 0.0);
    Bone* rupperlegx = new Bone("upleg_rx", cube);
    Joint* rhipx = new Joint("hip_rx", rupperlegx);
    rhipx->setTranslation(-0.15, -0.5, 0.0);
    rhipx->setRotationAxis(-1.0, 0.0, 0.0);
    torso->appendJoint(rhipx);
    cube = new Cube();
    cube->setScale(0.0, 0.0, 0.0);
    Bone* rupperlegy = new Bone("upleg_ry", cube);
    Joint* rhipy = new Joint("hip_ry", rupperlegy);
    rhipy->setRotationAxis(0.0, -1.0, 0.0);
    rupperlegx->appendJoint(rhipy);
    cube = new Cube();
    cube->setScale(0.1, 0.4, 0.075);
    cube->setTranslation(0.0, -0.4, 0.0);
    Bone* rupperlegz = new Bone("upleg_rz", cube);
    Joint* rhipz = new Joint("hip_rz", rupperlegz);
    rhipz->setRotationAxis(-1.0, 0.0, 0.0);
    rupperlegy->appendJoint(rhipz);
    cube = new Cube();
    cube->setScale(0.1, 0.3, 0.075);
    cube->setTranslation(0.0, -0.3, 0.0);
    Bone* rlowerleg = new Bone("lowleg_r", cube);
    Joint* rknee = new Joint("knee_r", rlowerleg);
    rknee->setTranslation(0.0, -0.8, 0.0);
    rknee->setRotationAxis(-1.0, 0.0, 0.0);
    rupperlegz->appendJoint(rknee);
    cube = new Cube();
    cube->setScale(0.1, 0.05, 0.2);
    cube->setTranslation(0.0, -0.05, 0.125);
    Bone* rfoot = new Bone("foot_r", cube);
    Joint* rankle = new Joint("ankle_r", rfoot);
    rankle->setTranslation(0.0, -0.6, 0.0);
    rankle->setRotationAxis(-1.0, 0.0, 0.0);
    rlowerleg->appendJoint(rankle);
    cube = new Cube();
    cube->setScale(0.0, 0.0, 0.0);
    Bone* lupperlegx = new Bone("upleg_lx", cube);
    Joint* lhipx = new Joint("hip_lx", lupperlegx);
    lhipx->setTranslation(0.15, -0.5, 0.0);
    lhipx->setRotationAxis(-1.0, 0.0, 0.0);
    torso->appendJoint(lhipx);
    cube = new Cube();
    cube->setScale(0.0, 0.0, 0.0);
    Bone* lupperlegy = new Bone("upleg_ly", cube);
    Joint* lhipy = new Joint("hip_ly", lupperlegy);
    lhipy->setRotationAxis(0.0, -1.0, 0.0);
    lupperlegx->appendJoint(lhipy);
    cube = new Cube();
    cube->setScale(0.1, 0.4, 0.075);
    cube->setTranslation(0.0, -0.4, 0.0);
    Bone* lupperlegz = new Bone("upleg_lz", cube);
    Joint* lhipz = new Joint("hip_lz", lupperlegz);
    lhipz->setRotationAxis(0.0, 0.0, -1.0);
    lupperlegy->appendJoint(lhipz);
    cube = new Cube();
    cube->setScale(0.1, 0.3, 0.075);
    cube->setTranslation(0.0, -0.3, 0.0);
    Bone* llowerleg = new Bone("lowleg_l", cube);
    Joint* lknee = new Joint("knee_l", llowerleg);
    lknee->setTranslation(0.0, -0.8, 0.0);
    lknee->setRotationAxis(-1.0, 0.0, 0.0);
    lupperlegz->appendJoint(lknee);
    cube = new Cube();
    cube->setScale(0.1, 0.05, 0.2);
    cube->setTranslation(0.0, -0.05, 0.125);
    Bone* lfoot = new Bone("foot_l", cube);
    Joint* lankle = new Joint("ankle_l", lfoot);
    lankle->setTranslation(0.0, -0.6, 0.0);
    lankle->setRotationAxis(-1.0, 0.0, 0.0);
    llowerleg->appendJoint(lankle);
}

void Skeleton::traverseJoint(Joint* j, JointTraverse& traverser) {
    traverser(j);
    Bone* node = j->getBone();
    vector<Joint*>::const_iterator i;
    for(i = node->begin(); i != node->end(); ++i) {
        traverseJoint(*i, traverser);
    }
}


void Skeleton::updateJoint(const Joint* j) const {
    Bone* node = j->getBone();
    glPushMatrix();
    Matrix44 t, r;
    t.SetTranslation(j->getTranslation()->val[0], j->getTranslation()->val[1], j->getTranslation()->val[2]);
    r.SetRotation(j->getRotationAngle()->getCurrDeg(), Vector3D(j->getRotationAxis()->val[0], j->getRotationAxis()->val[1], j->getRotationAxis()->val[2]));
    t *= r;
    glMultMatrixd(t[0]);
    node->getCube()->draw();
    vector<Joint*>::const_iterator i;
    for(i = node->begin(); i != node->end(); ++i) {
        updateJoint(*i);
    }
    glPopMatrix();
}
