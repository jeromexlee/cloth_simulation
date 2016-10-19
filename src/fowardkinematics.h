#ifndef FKFRAMER_H
#define FKFRAMER_H
#include <map>
#include <vector>
#include <string>
#include "../utils/timer.h"
#include "animation.h"

using namespace std;

class Frame {
public:
    Frame();
    double getDuration() const;
    void setDuration(double d);
    void addAngle(const string& name, double angle);
    map<string, double>::iterator begin();
    map<string, double>::iterator end();
    double operator[](const string& s);
private:
    double duration;
    map<string, double> frameAngles;
};

class FowardKinematics {
public:
    FowardKinematics();
    void setRate(double r);
    void update(map<string, DOF>& angles);
private:
    double rate;
    vector<Frame> frames;
    int currentFrame;
    int totalFrames;
    double frameStart;
    Timer timer;
};
#endif