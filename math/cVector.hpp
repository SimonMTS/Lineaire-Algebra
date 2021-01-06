#pragma once
#include <ostream>

#include "cMatrix.hpp"
using std::ostream;

class cVector {
 public:
  double X;
  double Y;
  double Z;
  double W = 1;

  cVector(const double x, const double y, const double z);

  double Length() const;
  cVector Normalized() const;

  double DotProduct(const cVector& other);
  cVector CrossProduct(const cVector& other);

  cVector operator*(const cMatrix& m);
  cVector operator+(const cMatrix& m);

  cVector operator-(const cVector& m);
  cVector operator+(const cVector& m);

  cVector operator-(const int n);
  cVector operator+(const int n);
  cVector operator*(const int n);

  void operator+=(cVector& other);
  void operator*=(cMatrix& m);
};

ostream& operator<<(ostream& Str, const cVector& p);
