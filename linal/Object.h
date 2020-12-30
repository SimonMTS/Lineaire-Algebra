#pragma once
#include "Line3D.h"
#include "Square.h"

class Object {
 public:
  vector<Square> Squares;

  void AddSquare(Square& l);

  void Scale(const double x, const double y, const double z);
  void Move(const double x, const double y, const double z);
  void Rotate(const int dir);
};
