#pragma once
#include <cmath>
#include <iomanip>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

#include <ostream>
using std::ostream;
using std::vector;

class cVector;

class cMatrix {
 private:
  vector<vector<double>> State;

 public:
  cMatrix(vector<vector<double>> state);

  static cMatrix GetTranslationMatrix(const double x, const double y,
                                      const double z);
  static cMatrix GetScalingMatrix(const double x, const double y,
                                  const double z);
  static cMatrix GetIdentityMatrix();
  static cMatrix GetRotationMatrix(const int axis, const double angle);
  static cMatrix GetRotationMatrix(const cVector& axis, const double angle);
  static cMatrix GetProjectionMatrix(const double near, const double far,
                                     const double fovy);

  static cMatrix RotationInverse(cMatrix& m);
  static cMatrix TranslationInverse(cMatrix& m);

  static cMatrix RotationOnly(cMatrix& m);
  static cMatrix TranslationOnly(cMatrix& m);

  vector<double>& operator[](const int i);
  vector<double> at(const int i) const;
  auto begin() const { return State.begin(); }
  auto end() const { return State.end(); }
  auto size() const { return State.size(); }

  cMatrix operator-(cMatrix& m);
  cMatrix operator+(cMatrix& m);

  cMatrix operator*(int i);
  cMatrix operator*(cMatrix m);

  void operator*=(cMatrix m);
};

ostream& operator<<(ostream& Str, cMatrix& m);
