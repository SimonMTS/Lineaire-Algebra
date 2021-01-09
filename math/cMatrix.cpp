#include "cMatrix.hpp"

#include <iostream>

#include "cVector.hpp"

cMatrix::cMatrix(vector<vector<double>> state) : State(state) {}

cMatrix cMatrix::GetTranslationMatrix(const double x, const double y,
                                      const double z) {
  vector<vector<double>> s(4, vector<double>(4, 0));
  s[0][0] = 1.0;
  s[1][1] = 1.0;
  s[2][2] = 1.0;
  s[3][3] = 1.0;

  s[0][3] = x;
  s[1][3] = y;
  s[2][3] = z;

  return cMatrix(s);
}

cMatrix cMatrix::GetScalingMatrix(const double x, const double y,
                                  const double z) {
  vector<vector<double>> s(4, vector<double>(4, 0));
  s[0][0] = x;
  s[1][1] = y;
  s[2][2] = z;

  s[3][3] = 1.0;

  return cMatrix(s);
}

cMatrix cMatrix::GetIdentityMatrix() {
  vector<vector<double>> s(4, vector<double>(4, 0));
  s[0][0] = 1;
  s[1][1] = 1;
  s[2][2] = 1;
  s[3][3] = 1;

  return cMatrix(s);
}

cMatrix cMatrix::GetRotationMatrix(const int axis, const double angle) {
  vector<vector<double>> s(4, vector<double>(4, 0));
  double r = angle * M_PI / 180;

  if (axis == 1) {  // x
    s[0][0] = 1;
    s[1][1] = cos(r);
    s[1][2] = sin(r);
    s[2][1] = -sin(r);
    s[2][2] = cos(r);
    s[3][3] = 1;
  } else if (axis == 2) {  // y
    s[0][0] = cos(r);
    s[0][2] = sin(r);
    s[1][1] = 1;
    s[2][0] = -sin(r);
    s[2][2] = cos(r);
    s[3][3] = 1;
  } else {  // z
    s[0][0] = cos(r);
    s[0][1] = -sin(r);
    s[1][0] = sin(r);
    s[1][1] = cos(r);
    s[2][2] = 1;
    s[3][3] = 1;
  }

  return cMatrix(s);
}

cMatrix cMatrix::GetRotationMatrix(const cVector& axis, const double angle) {
  cMatrix res = GetIdentityMatrix();

  // step 1 - rotate to xy plane
  cMatrix step1 = GetIdentityMatrix();
  {
    double cos = axis.X / sqrt((axis.X * axis.X) + (axis.Z * axis.Z));
    double sin = axis.Z / sqrt((axis.X * axis.X) + (axis.Z * axis.Z));

    {
      vector<vector<double>> s(4, vector<double>(4, 0));
      s[0][0] = cos != cos ? 1 : cos;
      s[2][0] = sin != sin ? 0 : sin;
      s[0][2] = -(sin != sin ? 0 : sin);
      s[2][2] = cos != cos ? 1 : cos;

      s[1][1] = 1;
      s[3][3] = 1;

      step1 = cMatrix(s);
    }

    res = res * step1;
  }

  // step 2 - rotate to x axis
  cMatrix step2 = GetIdentityMatrix();
  {
    double cos =
        sqrt((axis.X * axis.X) + (axis.Z * axis.Z)) /
        sqrt((axis.X * axis.X) + (axis.Y * axis.Y) + (axis.Z * axis.Z));
    double sin = axis.Y / sqrt((axis.X * axis.X) + (axis.Y * axis.Y) +
                               (axis.Z * axis.Z));

    {
      vector<vector<double>> s(4, vector<double>(4, 0));
      s[0][0] = cos != cos ? 1 : cos;
      s[1][0] = sin != sin ? 0 : sin;
      s[0][1] = -(sin != sin ? 0 : sin);
      s[1][1] = cos != cos ? 1 : cos;

      s[2][2] = 1;
      s[3][3] = 1;

      step2 = cMatrix(s);
    }

    res = res * step2;
  }

  // step 3 - rotate about the x axix
  res = res * GetRotationMatrix(1, angle);

  // step 4
  res = res * RotationInverse(step2);

  // step 5
  res = res * RotationInverse(step1);

  return res;
}

cMatrix cMatrix::GetProjectionMatrix(const double near, const double far,
                                     const double fovy) {
  vector<vector<double>> s(4, vector<double>(4, 0));
  double scale = near * tan(fovy * 0.5);

  s[0][0] = scale;
  s[1][1] = scale;
  s[2][2] = (-far) / (far - near);
  s[2][3] = -1;
  s[3][2] = ((-far) * near) / (far - near);

  return cMatrix(s);
}

cMatrix cMatrix::RotationInverse(cMatrix& m) {
  vector<vector<double>> s(4, vector<double>(4, 0));

  {
    s[3][0] = m[3][0];
    s[3][1] = m[3][1];
    s[3][2] = m[3][2];

    s[3][3] = m[3][3];

    s[0][3] = m[0][3];
    s[1][3] = m[1][3];
    s[2][3] = m[2][3];
  }

  s[0][0] = m[0][0];
  s[1][0] = m[0][1];
  s[2][0] = m[0][2];

  s[0][1] = m[1][0];
  s[1][1] = m[1][1];
  s[2][1] = m[1][2];

  s[0][2] = m[2][0];
  s[1][2] = m[2][1];
  s[2][2] = m[2][2];

  return cMatrix(s);
}

cMatrix cMatrix::TranslationInverse(cMatrix& m) {
  vector<vector<double>> s(4, vector<double>(4, 0));

  s[0][0] = m[0][0];
  s[0][1] = m[0][1];
  s[0][2] = m[0][2];
  s[0][3] = -m[0][3];

  s[1][0] = m[1][0];
  s[1][1] = m[1][1];
  s[1][2] = m[1][2];
  s[1][3] = -m[1][3];

  s[2][0] = m[2][0];
  s[2][1] = m[2][1];
  s[2][2] = m[2][2];
  s[2][3] = -m[2][3];

  s[3][0] = m[3][0];
  s[3][1] = m[3][1];
  s[3][2] = m[3][2];
  s[3][3] = m[3][3];

  return cMatrix(s);
}

cMatrix cMatrix::RotationOnly(cMatrix& m) {
  vector<vector<double>> s(4, vector<double>(4, 0));

  s[0][0] = m[0][0];  // 1;
  s[1][1] = m[1][1];  // 1;
  s[2][2] = m[2][2];  // 1;
  s[3][3] = m[3][3];  // 1;

  s[1][0] = m[1][0];
  s[2][0] = m[2][0];

  s[0][1] = m[0][1];
  s[2][1] = m[2][1];

  s[0][2] = m[0][2];
  s[1][2] = m[1][2];

  return cMatrix(s);
}

cMatrix cMatrix::TranslationOnly(cMatrix& m) {
  vector<vector<double>> s(4, vector<double>(4, 0));

  s[0][0] = 1;
  s[1][1] = 1;
  s[2][2] = 1;
  s[3][3] = 1;

  s[0][3] = m[0][3];
  s[1][3] = m[1][3];
  s[2][3] = m[2][3];

  return cMatrix(s);
}

vector<double>& cMatrix::operator[](int i) { return State[i]; }

vector<double> cMatrix::at(const int i) const { return State.at(i); }

cMatrix cMatrix::operator-(cMatrix& m) {
  vector<vector<double>> s(4, vector<double>(4, 0));

  for (int i = 0; i < (*this).size(); i++) {
    for (int j = 0; j < (*this)[i].size(); j++) {
      s[i][j] = (*this).State[i][j] - m[i][j];
    }
  }

  return cMatrix(s);
}

cMatrix cMatrix::operator+(cMatrix& m) {
  vector<vector<double>> s(4, vector<double>(4, 0));

  for (int i = 0; i < (*this).size(); i++) {
    for (int j = 0; j < (*this)[i].size(); j++) {
      s[i][j] = (*this).State[i][j] + m[i][j];
    }
  }

  return cMatrix(s);
}

cMatrix cMatrix::operator*(int i) {
  vector<vector<double>> s(4, vector<double>(4, 0));

  for (int i = 0; i < (*this).size(); i++) {
    for (int j = 0; j < (*this)[i].size(); j++) {
      s[i][j] = (*this).State[i][j] * i;
    }
  }

  return cMatrix(s);
}

cMatrix cMatrix::operator*(cMatrix m) {
  vector<vector<double>> s(4, vector<double>(4, 0));

  for (int i = 0; i < (*this).size(); i++) {
    for (int j = 0; j < m.size(); j++) {
      s[i][j] = (*this)[i][0] * m[0][j] + (*this)[i][1] * m[1][j] +
                (*this)[i][2] * m[2][j] + (*this)[i][3] * m[3][j];
    }
  }

  return cMatrix(s);
}

void cMatrix::operator*=(cMatrix m) { (*this) = (*this) * m; }

ostream& operator<<(ostream& Str, cMatrix& m) {
  Str << std::fixed;
  Str << std::setprecision(4);

  for (const auto& row : m) {
    Str << "[ ";
    for (const auto& col : row) {
      if (col >= 0) Str << " ";
      Str << col << " ";
    }
    Str << "]\n";
  }

  return Str;
}
