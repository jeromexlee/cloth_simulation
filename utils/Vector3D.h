#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <math.h>
#include <iostream>

class Vector3D {
public:
	float val[3];
	Vector3D(float x, float y, float z);
	Vector3D();
	Vector3D operator+ (const Vector3D &v);
	Vector3D operator- (const Vector3D &v);
	Vector3D operator* (const float &n);
	Vector3D operator/ (const float &n);
	Vector3D operator- ();
	void operator+= (const Vector3D &v);
	void operator-= (const Vector3D &v);
	void operator*= (const float &n);
	void operator/= (const float &n);
	float length();
	Vector3D norm();
	Vector3D cross(const Vector3D &v);
	float dot(const Vector3D &v);
};

#endif