#ifndef MATRIX44_H
#define MATRIX44_H

#include "Vector3D.h"
#include "matrix.h"

class Matrix44 : public Matrix
{
public:
  Matrix44() : Matrix(4, 4) { }

  // this = A * B - adjusted for column major ordering used for interoperability with OpenGL
  virtual bool Mult(const Matrix& A, const Matrix& B) { return Matrix::Mult(B, A); }

  void Transform(const Vector3D &in, Vector3D &out) const;

  void SetTranslation(double x, double y, double z);
  void SetTranslation(const Vector3D& t) { SetTranslation(t.val[0], t.val[1], t.val[2]); }
  void SetRotation(double angle, double x, double y, double z) { SetRotation(angle, Vector3D(x, y, z)); }
  void SetRotation(double angle, const Vector3D& axis);
  void SetRotationX(double angle);
  void SetRotationY(double angle);
  void SetRotationZ(double angle);
  void SetScale(double x, double y, double z);
  void SetScale(const Vector3D& s) { SetScale(s.val[0], s.val[1], s.val[2]); }

  // Set the camera position
  void SetView(Vector3D& LookAt, Vector3D& Viewer, const Vector3D& UpL);

  //Do perspective projection with near and far clipping planes and window height
  void SetPerspective(double D, double F, double H);

  //Project with focal length
  void SetPerspective(double depth);

  Vector3D operator*(const Vector3D& V) { Vector3D out; Transform(V, out); return out; }
};

#endif
