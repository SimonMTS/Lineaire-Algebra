#pragma once
#include "../math/cVector.hpp"

class Square {
 public:
  cVector P1;
  cVector P2;
  cVector P3;
  cVector P4;

  Square(const cVector& p1, const cVector& p2, const cVector& p3,
         const cVector& p4);
};
