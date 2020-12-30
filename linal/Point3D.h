#pragma once
#include <ostream>

#include "Matrix3D.h"
using std::ostream;

class Point3D {
 public:
  double X;
  double Y;
  double Z;
  double W = 1;

  Point3D(double x, double y, double z);

  int InProduct(Point3D other);
  Point3D OutProduct(Point3D other);

  Point3D operator*(Matrix3D m);
  Point3D operator+(Matrix3D m);

  Point3D operator-(Point3D m);
};

ostream& operator<<(ostream& Str, Point3D p);