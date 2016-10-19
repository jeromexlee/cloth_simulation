#ifndef DOF_H
#define DOF_H

#include <string>
#include <map>

using namespace std;

class DOF {
public:

    DOF(double deg = 0.0, double l = -360.0, double u = 360.0) {  
        lower = l;
        upper = u;
        updateDeg(deg);
    }

    double getCurrDeg() const { 
        return curr_deg; 
    }

    void updateDeg(double value) {
        if (value < lower) {
            curr_deg = lower;
        } else if(value > upper) {
            curr_deg = upper;
        } else {
            curr_deg = value;
        }
    }

private:
    double lower;
    double upper;
    double curr_deg;
};

#endif