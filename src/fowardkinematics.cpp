#include "fowardkinematics.h"
#define FRAMEDURATION 1.0

using namespace std;

Frame::Frame() { 
    duration = 0.0;
}

double Frame::getDuration() const { 
    return duration; 
}

void Frame::setDuration(double d) { 
    duration = d;
}

void Frame::addAngle(const string& name, double angle) { 
    frameAngles.insert(make_pair(name, angle)); 
}

map<string, double>::iterator Frame::begin() { 
    return frameAngles.begin(); 
}

map<string, double>::iterator Frame::end() { 
    return frameAngles.end(); 
}

double Frame::operator[](const string& s) { 
    return frameAngles[s]; 
}

void FowardKinematics::setRate(double r) { 
    rate = r; 
}

FowardKinematics::FowardKinematics() {
    currentFrame = 0;
    totalFrames = 0;
    frameStart = -1.0;
    totalFrames = 8;
    Frame f1, f2, f3, f4, f5, f6, f7, f8;
    f1.setDuration(FRAMEDURATION);
    f1.addAngle("hip_rx", 0.0);
    f1.addAngle("knee_r", 0.0);
    f1.addAngle("ankle_r", 0.0);
    f1.addAngle("hip_lx", 0.0);
    f1.addAngle("knee_l", 0.0);
    f1.addAngle("ankle_l", 0.0);
    f1.addAngle("shoulder_rx", 0.0);
    f1.addAngle("elbow_r", 0.0);
    f1.addAngle("shoulder_lx", 0.0);
    f1.addAngle("elbow_l", 0.0);
    f2.setDuration(FRAMEDURATION);
    f2.addAngle("hip_rx", 22.5);
    f2.addAngle("knee_r", -17.5);
    f2.addAngle("ankle_r", -17.5);
    f2.addAngle("hip_lx", -17.5);
    f2.addAngle("knee_l", 0.0);
    f2.addAngle("ankle_l", 10.0);
    f2.addAngle("shoulder_rx", -22.5);
    f2.addAngle("elbow_r", 17.5);
    f2.addAngle("shoulder_lx", 17.5);
    f2.addAngle("elbow_l", 0.0);
    f3.setDuration(FRAMEDURATION);
    f3.addAngle("hip_rx", 45.0);
    f3.addAngle("knee_r", -35.0);
    f3.addAngle("ankle_r", -35.0);
    f3.addAngle("hip_lx", -35.0);
    f3.addAngle("knee_l", -30.0);
    f3.addAngle("ankle_l", -8.0);
    f3.addAngle("shoulder_rx", -45.0);
    f3.addAngle("elbow_r", 35.0);
    f3.addAngle("shoulder_lx", 35.0);
    f3.addAngle("elbow_l", 30.0);
    f4.setDuration(FRAMEDURATION);
    f4.addAngle("hip_rx", 22.5);
    f4.addAngle("knee_r", 0.0);
    f4.addAngle("ankle_r", 0.0);
    f4.addAngle("hip_lx", -17.5);
    f4.addAngle("knee_l", -15.0);
    f4.addAngle("ankle_l", -5.0);
    f4.addAngle("shoulder_rx", -22.5);
    f4.addAngle("elbow_r", 0.0);
    f4.addAngle("shoulder_lx", 17.5);
    f4.addAngle("elbow_l", 15.0);
    f5.setDuration(FRAMEDURATION);
    f5.addAngle("hip_rx", 0.0);
    f5.addAngle("knee_r", 0.0);
    f5.addAngle("ankle_r", 0.0);
    f5.addAngle("hip_lx", 0.0);
    f5.addAngle("knee_l", 0.0);
    f5.addAngle("ankle_l", 0.0);
    f5.addAngle("shoulder_rx", 0.0);
    f5.addAngle("elbow_r", 0.0);
    f5.addAngle("shoulder_lx", 0.0);
    f5.addAngle("elbow_l", 0.0);
    f6.setDuration(FRAMEDURATION);
    f6.addAngle("hip_rx", -17.5);
    f6.addAngle("knee_r", 0.0);
    f6.addAngle("ankle_r", 10.0);
    f6.addAngle("hip_lx", 22.5);
    f6.addAngle("knee_l", -17.5);
    f6.addAngle("ankle_l", -17.5);
    f6.addAngle("shoulder_rx", 17.5);
    f6.addAngle("elbow_r", 0.0);
    f6.addAngle("shoulder_lx", -22.5);
    f6.addAngle("elbow_l", 17.5);
    f7.setDuration(FRAMEDURATION);
    f7.addAngle("hip_rx", -35.0);
    f7.addAngle("knee_r", -30.0);
    f7.addAngle("ankle_r", -8.0);
    f7.addAngle("hip_lx", 45.0);
    f7.addAngle("knee_l", -35.0);
    f7.addAngle("ankle_l", -35.0);
    f7.addAngle("shoulder_rx", 35.0);
    f7.addAngle("elbow_r", 30.0);
    f7.addAngle("shoulder_lx", -45.0);
    f7.addAngle("elbow_l", 35.0);
    f8.setDuration(FRAMEDURATION);
    f8.addAngle("hip_rx", -17.5);
    f8.addAngle("knee_r", -15.0);
    f8.addAngle("ankle_r", -5.0);
    f8.addAngle("hip_lx", 22.5);
    f8.addAngle("knee_l", 0.0);
    f8.addAngle("ankle_l", 0.0);
    f8.addAngle("shoulder_rx", 17.5);
    f8.addAngle("elbow_r", 15.0);
    f8.addAngle("shoulder_lx", -22.5);
    f8.addAngle("elbow_l", 0.0);
    frames.push_back(f1);
    frames.push_back(f2);
    frames.push_back(f3);
    frames.push_back(f4);
    frames.push_back(f5);
    frames.push_back(f6);
    frames.push_back(f7);
    frames.push_back(f8);
    frames.push_back(f1);
}

void FowardKinematics::update(map<string, DOF>& angles) {
    if (frameStart < 0.0) {
        frameStart = timer.getTime();
    }
    double t = timer.getTime() - frameStart;
    t *= rate;
    if(t > frames[currentFrame].getDuration()) {
        currentFrame = (currentFrame + 1) % totalFrames;
        frameStart = timer.getTime();
        t = 0.0;
    }
    double a = t / frames[currentFrame].getDuration();
    map<string, double>::const_iterator iter;
    for(iter = frames[currentFrame].begin(); iter != frames[currentFrame].end(); ++iter) {
        angles[iter->first].updateDeg(iter->second + ((frames[currentFrame + 1][iter->first] - iter->second) * a));
    }
}
