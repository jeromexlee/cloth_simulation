#include "Vector3D.h"

Vector3D::Vector3D(float x, float y, float z) {
	val[0] = x; 
	val[1] = y; 
	val[2] = z;
}

Vector3D::Vector3D() {
	val[0] = 0; 
	val[1] = 0; 
	val[2] = 0;
}

Vector3D Vector3D::operator+ (const Vector3D &v) {
	return Vector3D(val[0]+v.val[0], 
					val[1]+v.val[1], 
					val[2]+v.val[2]);
}

Vector3D Vector3D::operator- (const Vector3D &v) {
	return Vector3D(val[0]-v.val[0], 
					val[1]-v.val[1], 
					val[2]-v.val[2]);
}

Vector3D Vector3D::operator* (const float &n) {
	return Vector3D(val[0]*n, 
					val[1]*n,
					val[2]*n);
}

Vector3D Vector3D::operator/ (const float &n) {
	return Vector3D(val[0]/n,
				 	val[1]/n, 
				 	val[2]/n);
}

Vector3D Vector3D::operator- () {
	return Vector3D(-val[0],
					-val[1],
					-val[2]);
}

void Vector3D::operator+= (const Vector3D &v) {
	val[0] += v.val[0];
	val[1] += v.val[1];
	val[2] += v.val[2];
}

void Vector3D::operator-= (const Vector3D &v) {
	val[0] -= v.val[0];
	val[1] -= v.val[1];
	val[2] -= v.val[2];
}

void Vector3D::operator*= (const float &n) {
	val[0] *= n;
	val[1] *= n;
	val[2] *= n;
}

void Vector3D::operator/= (const float &n) {
	val[0] /= n;
	val[1] /= n;
	val[2] /= n;
}

float Vector3D::length() {
	return sqrt(val[0]*val[0] + 
				val[1]*val[1] + 
				val[2]*val[2]);
}

Vector3D Vector3D::norm() {
	float len = length();
	return Vector3D(val[0]/len, 
					val[1]/len, 
					val[2]/len);
}

float Vector3D::dot(const Vector3D &v) {
	return val[0]*v.val[0] + val[1]*v.val[1] + val[2]*v.val[2];
}

Vector3D Vector3D::cross(const Vector3D &v) {
	return Vector3D(val[1]*v.val[2] - val[2]*v.val[1], 
					val[2]*v.val[0] - val[0]*v.val[2], 
					val[0]*v.val[1] - val[1]*v.val[0]);
}