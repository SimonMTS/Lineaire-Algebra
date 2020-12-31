#pragma once
#include <vector>

#include "Component.hpp"
using std::vector;

class Structure {
 public:
  //cMatrix State = cMatrix::GetScalingMatrix(1, 1, 1); // empty matrix

  cVector Pos = {0, 0, 0};
  cVector Dir = {0, 0, 1};
  double Rot = 0;

  vector<Component> Components;

  void AddComponent(const Component& c);

  void operator*=(const cMatrix& m);
};
