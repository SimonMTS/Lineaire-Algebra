#pragma once
#include <vector>

#include "Component.hpp"
using std::vector;

class Structure {
 public:
  cMatrix State = cMatrix::GetIdentityMatrix();

  vector<Component> Components;

  void AddComponent(const Component& c);

  void operator*=(const cMatrix& m);
};
