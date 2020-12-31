#pragma once
#include <tuple>

#include "Object.h"
#include "Point3D.h"
using std::get;
using std::pair;
using std::tuple;

class Structure {
 public:
  vector<pair<Point3D, Object>> Objects;

  //tuple<int, int, int> Rotation = {0, 0, 0};
  Matrix3D Rot = Matrix3D::GetScalingMatrix(1, 1, 1);

  void AddObject(pair<Point3D, Object>& o);

  void Scale(const double x, const double y, const double z);
  void Move(const double x, const double y, const double z);
  void Rotate(const int dir, const int angle);
};
