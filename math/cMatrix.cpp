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
    s[3][1] = m[3][2];
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

bool gluInvertMatrix(const double m[16], double invOut[16]);
cMatrix cMatrix::Inverse(cMatrix& m) {
  double in[16];
  {
    in[ 0] = m[0][0];
    in[ 1] = m[1][0];
    in[ 2] = m[2][0];
    in[ 3] = m[3][0];
    in[ 4] = m[0][1];
    in[ 5] = m[1][1];
    in[ 6] = m[2][1];
    in[ 7] = m[3][1];
    in[ 8] = m[0][2];
    in[ 9] = m[1][2];
    in[10] = m[2][2];
    in[11] = m[3][2];
    in[12] = m[0][3];
    in[13] = m[1][3];
    in[14] = m[2][3];
    in[15] = m[3][3];
  }
  double out[16];

  if (gluInvertMatrix(in, out)) {
    vector<vector<double>> s(4, vector<double>(4, 0));

    s[0][0] = out[0];
    s[1][0] = out[1];
    s[2][0] = out[2];
    s[3][0] = out[3];
    s[0][1] = out[4];
    s[1][1] = out[5];
    s[2][1] = out[6];
    s[3][1] = out[7];
    s[0][2] = out[8];
    s[1][2] = out[9];
    s[2][2] = out[10];
    s[3][2] = out[11];
    s[0][3] = out[12];
    s[1][3] = out[13];
    s[2][3] = out[14];
    s[3][3] = out[15];

    //delete[] in;
    //delete[] out;
    return cMatrix(s);
  }

  //delete[] in;
  //delete[] out;
  return m;
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


bool gluInvertMatrix(const double m[16], double invOut[16]) {
  double inv[16], det;
  int i;

  inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] +
           m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];

  inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] -
           m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];

  inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] +
           m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];

  inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] -
            m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];

  inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] -
           m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];

  inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] +
           m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];

  inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] -
           m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];

  inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] +
            m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];

  inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] +
           m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];

  inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] -
           m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];

  inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] +
            m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];

  inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] -
            m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];

  inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] -
           m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];

  inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] +
           m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];

  inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] -
            m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];

  inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] +
            m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

  det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

  if (det == 0) return false;

  det = 1.0 / det;

  for (i = 0; i < 16; i++) invOut[i] = inv[i] * det;

  return true;
}