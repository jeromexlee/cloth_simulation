#ifndef CUBE_H
#define CUBE_H

#include "../utils/Vector3D.h"

class Cube
{
protected:
  Vector3D scale_;
  double rotAngle_;
  Vector3D rotAxis_;
  Vector3D trans_;
  void polygon(int a, int b, int c, int d, int facenum);
public:
  Cube() : rotAngle_(0.0) { }
  Vector3D* getScale() const { return (Vector3D*)&scale_; }
  double getRotationAngle() const { return rotAngle_; }
  Vector3D* getRotationAxis() const { return (Vector3D*)&rotAxis_; }
  Vector3D* getTranslation() const { return (Vector3D*)&trans_; }

  void setScale(double x, double y, double z) { scale_.val[0] = (float)x; scale_.val[1] = (float)y; scale_.val[2] = (float)z; }
  void setScale(const Vector3D& scale) { scale_ = scale; }
  void setRotationAngle(double angle) { rotAngle_ = angle; }
  void setRotationAxis(double x, double y, double z) { rotAxis_.val[0] = (float)x; rotAxis_.val[1] = (float)y; rotAxis_.val[2] = (float)z; }
  void setRotationAxis(const Vector3D& rot) { rotAxis_ = rot; }
  void setTranslation(double x, double y, double z) { trans_.val[0] = (float)x; trans_.val[1] = (float)y; trans_.val[2] = (float)z; }
  void setTranslation(const Vector3D& trans) { trans_ = trans; }

  void draw();
  
};

#endif
