#include "animation.h"

Animation::Animation(Skeleton* s, FowardKinematics* f) {
    skeleton = s;
    framer = f;
    Initializer initialState(angles);
    s->traverseJoints(initialState);
}

void Animation::update() {
    framer->update(angles);
    Updater updater(angles);
    skeleton->traverseJoints(updater);
}

void Animation::draw() {
    skeleton->update();
}
