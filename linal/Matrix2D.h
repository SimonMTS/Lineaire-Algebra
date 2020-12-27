#pragma once
#include <cmath>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
using std::vector;

class Matrix2D {
 private:
  vector<vector<double>> State;
  double RoundToWholeRad(double n);

 public:
  Matrix2D(vector<vector<double>> state);

  static Matrix2D GetTranslationMatrix(const double x, const double y);
  static Matrix2D GetScalingMatrix(const double x, const double y);
  static Matrix2D GetRotationMatrix(const double angle);

  vector<double> operator[](int i);
  auto begin() const { return State.begin(); }
  auto end() const { return State.end(); }
  auto size() const { return State.size(); }

  Matrix2D operator-(Matrix2D m);
  Matrix2D operator+(Matrix2D m);
  Matrix2D operator*(int i);
  Matrix2D operator*(Matrix2D m);
};
