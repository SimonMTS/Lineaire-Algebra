#pragma once
#include <vector>

#include "Square.hpp"
using std::vector;

class Component {
 public:
  vector<Square> Squares;

  cVector Pos = {0, 0, 0};

  void AddSquare(const Square& l);

  void operator*=(const cMatrix& m);
};
