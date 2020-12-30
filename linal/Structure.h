#pragma once
#include "Object.h"
#include "Point3D.h"
using std::pair;

class Structure {
 public:
  vector<pair<Point3D, Object>> Objects;

  void AddObject(pair<Point3D, Object>& o);

   void Scale(const double x, const double y, const double z);
   void Move(const double x, const double y, const double z);
   void Rotate(const int dir);
};
