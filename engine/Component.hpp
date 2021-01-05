#pragma once
#include <vector>

#include "Square.hpp"
using std::vector;

class Component {
 public:
  vector<Square> Squares;

  cVector Pos = {0, 0, 0};

  void AddSquare(const Square& l);

  // void Scale(const double x, const double y, const double z);
  // void Move(const double x, const double y, const double z);
  // void Rotate(const int dir);
};
