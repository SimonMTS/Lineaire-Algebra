#pragma once
#include "Line3D.h"

class Object {
 public:
  vector<Line3D> Lines;

  void AddLine(Line3D& l);

  void Scale(const double x, const double y, const double z);
  void Move(const double x, const double y, const double z);
  void Rotate(const int dir);
};
