#include "Matrix2D.h"

double Matrix2D::RoundToWholeRad(double n) {
  double floor = std::floor(n) + 0.99;
  double ceiling = std::ceil(n) + 0.01;
  if (n > floor && n < ceiling) return ceiling;

  return n;
}

Matrix2D::Matrix2D(vector<vector<double>> state) : State(state) {}

Matrix2D Matrix2D::GetTranslationMatrix(const double x, const double y) {
  vector<vector<double>> s(3, vector<double>(3, 0));
  s[0][0] = 1.0;
  s[0][1] = 0.0;
  s[0][2] = x;
  s[1][0] = 0.0;
  s[1][1] = 1.0;
  s[1][2] = y;
  s[2][0] = 0.0;
  s[2][1] = 0.0;
  s[2][2] = 1.0;

  return Matrix2D(s);
}

Matrix2D Matrix2D::GetScalingMatrix(const double x, const double y) {
  vector<vector<double>> s(3, vector<double>(3, 0));
  s[0][0] = x;
  s[1][1] = y;
  s[2][2] = 1;

  return Matrix2D(s);
}

Matrix2D Matrix2D::GetRotationMatrix(const double angle) {
  vector<vector<double>> s(3, vector<double>(3, 0));
  double r = angle * M_PI / 180;

  s[0][0] = cos(r);
  s[0][1] = sin(r);
  s[1][0] = -sin(r);
  s[1][1] = cos(r);
  s[2][2] = 1;

  return Matrix2D(s);
}

vector<double> Matrix2D::operator[](int i) { return State.at(i); }

Matrix2D Matrix2D::operator-(Matrix2D m) {
  vector<vector<double>> s(3, vector<double>(3, 0));

  for (int i = 0; i < (*this).size(); i++) {
    for (int j = 0; j < (*this)[i].size(); j++) {
      s[i][j] = (*this).State[i][j] - m[i][j];
    }
  }

  return Matrix2D(s);
}

Matrix2D Matrix2D::operator+(Matrix2D m) {
  vector<vector<double>> s(3, vector<double>(3, 0));

  for (int i = 0; i < (*this).size(); i++) {
    for (int j = 0; j < (*this)[i].size(); j++) {
      s[i][j] = (*this).State[i][j] + m[i][j];
    }
  }

  return Matrix2D(s);
}

Matrix2D Matrix2D::operator*(int i) {
  vector<vector<double>> s(3, vector<double>(3, 0));

  for (int i = 0; i < (*this).size(); i++) {
    for (int j = 0; j < (*this)[i].size(); j++) {
      s[i][j] = (*this).State[i][j] * i;
    }
  }

  return Matrix2D(s);
}

Matrix2D Matrix2D::operator*(Matrix2D m) {
  vector<vector<double>> s(3, vector<double>(3, 0));

  for (int i = 0; i < (*this).size(); i++) {
    for (int j = 0; j < m.size(); j++) {
      s[i][j] = (*this)[i][0] * m[0][j] + (*this)[i][1] * m[1][j] +
                (*this)[i][2] * m[2][j];
    }
  }

  return Matrix2D(s);
}
