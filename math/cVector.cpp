#include "cVector.hpp"

cVector::cVector(const double x, const double y, const double z)
    : X(x), Y(y), Z(z) {}

double cVector::Length() const { return sqrt((X * X) + (Y * Y) + (Z * Z)); }

cVector cVector::Normalized() const {
  double len = Length();

  if (len == 1) {
    return {X, Y, Z};
  }

  return {X / len, Y / len, Z / len};
}

double cVector::DotProduct(const cVector& other) {
  return (this->X * other.X) + (this->Y * other.Y) + (this->Z * other.Z);
}

cVector cVector::CrossProduct(const cVector& other) {
  double x = this->Y * other.Z - this->Z * other.Y;
  double y = this->Z * other.X - this->X * other.Z;
  double z = this->X * other.Y - this->Y * other.X;

  return cVector(x, y, z);
}

cVector cVector::operator*(const cMatrix& m) {
  cVector p(this->X, this->Y, this->Z);
  p.X = (m.at(0)[0] * this->X) + (m.at(0)[1] * this->Y) +
        (m.at(0)[2] * this->Z) + (m.at(0)[3] * this->W);
  p.Y = (m.at(1)[0] * this->X) + (m.at(1)[1] * this->Y) +
        (m.at(1)[2] * this->Z) + (m.at(1)[3] * this->W);
  p.Z = (m.at(2)[0] * this->X) + (m.at(2)[1] * this->Y) +
        (m.at(2)[2] * this->Z) + (m.at(2)[3] * this->W);
  p.W = (m.at(3)[0] * this->X) + (m.at(3)[1] * this->Y) +
        (m.at(3)[2] * this->Z) + (m.at(3)[3] * this->W);

  return p;
}

cVector cVector::operator+(const cMatrix& m) {
  cVector p(this->X, this->Y, this->Z);
  p.X = (m.at(0)[0] + this->X) + (m.at(0)[1] + this->Y) +
        (m.at(0)[2] + this->Z) + (m.at(0)[3] + this->W);
  p.Y = (m.at(1)[0] + this->X) + (m.at(1)[1] + this->Y) +
        (m.at(1)[2] + this->Z) + (m.at(1)[3] + this->W);
  p.Z = (m.at(2)[0] + this->X) + (m.at(2)[1] + this->Y) +
        (m.at(2)[2] + this->Z) + (m.at(2)[3] + this->W);
  p.W = (m.at(3)[0] + this->X) + (m.at(3)[1] + this->Y) +
        (m.at(3)[2] + this->Z) + (m.at(3)[3] + this->W);

  return p;
}

cVector cVector::operator-(const cVector& other) {
  cVector p(this->X, this->Y, this->Z);
  p.X = this->X - other.X;
  p.Y = this->Y - other.Y;
  p.Z = this->Z - other.Z;

  return p;
}

cVector cVector::operator+(const cVector& other) {
  cVector p(this->X, this->Y, this->Z);
  p.X = this->X + other.X;
  p.Y = this->Y + other.Y;
  p.Z = this->Z + other.Z;

  return p;
}

cVector cVector::operator-(const int n) {
  cVector p(this->X, this->Y, this->Z);
  p.X = this->X + n;
  p.Y = this->Y + n;
  p.Z = this->Z + n;

  return p;
}

cVector cVector::operator+(const int n) {
  cVector p(this->X, this->Y, this->Z);
  p.X = this->X + n;
  p.Y = this->Y + n;
  p.Z = this->Z + n;

  return p;
}

cVector cVector::operator*(const int n) {
  cVector p(this->X, this->Y, this->Z);
  p.X = this->X * n;
  p.Y = this->Y * n;
  p.Z = this->Z * n;

  return p;
}

ostream& operator<<(ostream& Str, const cVector& p) {
  return Str << "[" << p.X << ", " << p.Y << ", " << p.Z << "]";
}