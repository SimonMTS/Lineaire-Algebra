#include "Point3D.h"

Point3D::Point3D(double x, double y, double z) : X(x), Y(y), Z(z) {}

int Point3D::InProduct(Point3D other) {
  return this->X * other.X + this->Y * other.Y + this->Z * other.Z;
}

Point3D Point3D::OutProduct(Point3D other) {
  double x = this->Y * other.Z - this->Z * other.Y;
  double y = this->Z * other.X - this->X * other.Z;
  double z = this->X * other.Y - this->Y * other.X;

  return Point3D(x, y, z);
}

Point3D Point3D::operator*(Matrix3D m) {
  Point3D p(this->X, this->Y, this->Z);
  p.X = m[0][0] * this->X + m[0][1] * this->Y + m[0][2] * this->Z +
        m[0][3] * this->W;
  p.Y = m[1][0] * this->X + m[1][1] * this->Y + m[1][2] * this->Z +
        m[1][3] * this->W;
  p.Z = m[2][0] * this->X + m[2][1] * this->Y + m[2][2] * this->Z +
        m[2][3] * this->W;
  p.W = m[3][0] * this->X + m[3][1] * this->Y + m[3][2] * this->Z +
        m[3][3] * this->W;

  return p;
}

Point3D Point3D::operator+(Matrix3D m) {
  Point3D p(this->X, this->Y, this->Z);
  p.X = m[0][0] + this->X + m[0][1] + this->Y + m[0][2] + this->Z + m[0][3] +
        this->W;
  p.Y = m[1][0] + this->X + m[1][1] + this->Y + m[1][2] + this->Z + m[1][3] +
        this->W;
  p.Z = m[2][0] + this->X + m[2][1] + this->Y + m[2][2] + this->Z + m[2][3] +
        this->W;
  p.W = m[3][0] + this->X + m[3][1] + this->Y + m[3][2] + this->Z + m[3][3] +
        this->W;

  return p;
}

ostream& operator<<(ostream& Str, Point3D p) {
  // print something from v to str, e.g: Str << v.getX();
  return Str << "[" << p.X << ", " << p.Y << ", " << p.Z << "]";
}