#include <math.h>
#include "matrix44.h"

#ifndef DEG2RAD
#define DEG2RAD  0.017453292519943295769236907684886
#endif

void Matrix44::Transform(const Vector3D &in, Vector3D &out) const
{
  double x, y, z, denom;
  x = in.val[0] * matrix_[0][0] + 
      in.val[1] * matrix_[1][0] + 
      in.val[2] * matrix_[2][0] +
      matrix_[3][0];

  y = in.val[0] * matrix_[0][1] + 
      in.val[1] * matrix_[1][1] + 
      in.val[2] * matrix_[2][1] +
      matrix_[3][1];

  z = in.val[0] * matrix_[0][2] + 
      in.val[1] * matrix_[1][2] + 
      in.val[2] * matrix_[2][2] +
      matrix_[3][2];

  out.val[0] = x;
  out.val[1] = y;
  out.val[2] = z;

  denom = matrix_[0][3] + matrix_[1][3] + matrix_[2][3] + matrix_[3][3];
  if(denom != 1.0)
    out /= denom;
}

void Matrix44::SetTranslation(double x, double y, double z)
{
  SetIdentity();

  matrix_[3][0] = x;
  matrix_[3][1] = y;
  matrix_[3][2] = z;
}

void Matrix44::SetRotation(double angle, const Vector3D& axis)
{
  Vector3D u(axis);
  double Cosine = cos(angle * DEG2RAD);
  double Sine = sin(angle * DEG2RAD);
  double oneMinus = 1.0 - Cosine;

  SetIdentity();

  u.norm();

  matrix_[0][0] = oneMinus * u.val[0] * u.val[0] + Cosine;
  matrix_[1][1] = oneMinus * u.val[1] * u.val[1] + Cosine;
  matrix_[2][2] = oneMinus * u.val[2] * u.val[2] + Cosine;
  matrix_[0][1] = oneMinus * u.val[0] * u.val[1] + Sine * u.val[2];
  matrix_[1][0] = oneMinus * u.val[0] * u.val[1] - Sine * u.val[2];
  matrix_[0][2] = oneMinus * u.val[0] * u.val[2] - Sine * u.val[1];
  matrix_[2][0] = oneMinus * u.val[0] * u.val[2] + Sine * u.val[1];
  matrix_[1][2] = oneMinus * u.val[1] * u.val[2] + Sine * u.val[0];
  matrix_[2][1] = oneMinus * u.val[1] * u.val[2] - Sine * u.val[0];
}

void Matrix44::SetRotationX(double angle)
{
  double Cosine = cos(angle * DEG2RAD);
  double Sine = sin(angle * DEG2RAD);

  SetIdentity();

  matrix_[1][1] = Cosine;
  matrix_[2][1] = -Sine;
  matrix_[1][2] = Sine;
  matrix_[2][2] = Cosine;
}

void Matrix44::SetRotationY(double angle)
{
  double Cosine = cos(angle * DEG2RAD);
  double Sine = sin(angle * DEG2RAD);

  SetIdentity();

  matrix_[0][0] = Cosine;
  matrix_[2][0] = -Sine;
  matrix_[0][2] = Sine;
  matrix_[2][2] = Cosine;
}

void Matrix44::SetRotationZ(double angle)
{
  double Cosine = cos(angle * DEG2RAD);
  double Sine = sin(angle * DEG2RAD);

  SetIdentity();

  matrix_[0][0] = Cosine;
  matrix_[1][0] = -Sine;
  matrix_[0][1] = Sine;
  matrix_[1][1] = Cosine;
}

void Matrix44::SetScale(double x, double y, double z)
{
  SetIdentity();

  matrix_[0][0] = x;
  matrix_[1][1] = y;
  matrix_[2][2] = z;
}

void Matrix44::SetView(Vector3D& LookAt, Vector3D& Viewer, const Vector3D& UpL)
{
  int i;
  Matrix44 M, T;
  Vector3D U, V;
  Vector3D Up = UpL;
  Vector3D N = LookAt - Viewer;

  M.SetIdentity();
  T.SetTranslation(-Viewer.val[0], -Viewer.val[1], -Viewer.val[2]);
  
  Up.norm();
  N.norm();

  V = Up - (N * Up.dot(N));
  V. norm();

  U = N.cross(V);
  U.norm();

  for (i = 0; i < 3; i++)
  {
    M.matrix_[i][0] = U.val[i]; 
    M.matrix_[i][1] = V.val[i]; 
    M.matrix_[i][2] = N.val[i]; 
  }

  Mult(T, M);
}

//Do perspective projection with near and far clipping planes and window height
void Matrix44::SetPerspective(double D, double F, double H)
{
  SetIdentity();

  matrix_[2][2] = (H * F) / (D * (F - D));
  matrix_[2][3] = H/D;
  matrix_[3][2] = ((-1.0 * H) * F) / (F - D);
  matrix_[3][3] = 0.0;
}

//Project with focal length
void Matrix44::SetPerspective(double depth)
{
  SetIdentity();

  matrix_[2][3] = 1.0/depth;
  matrix_[3][3] = 0.0;
}
