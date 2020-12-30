#include "Object.h"

void Object::AddSquare(Square& s) { Squares.push_back(s); }

void Object::Scale(const double x, const double y, const double z) {}

void Object::Move(const double x, const double y, const double z) {}

void Object::Rotate(const int dir) {
  Point3D localOrigin = {0, 0, 0};

  Matrix3D tm1 = Matrix3D::GetTranslationMatrix(
      -localOrigin.X, -localOrigin.Y, -localOrigin.Z);
  Matrix3D tm2 = Matrix3D::GetTranslationMatrix(
      localOrigin.X, localOrigin.Y, localOrigin.Z);
  Matrix3D rm = Matrix3D::GetRotationMatrix(abs(dir), (dir > 0 ? 1 : -1));
  Matrix3D cm = tm2 * rm * tm1;

  for (auto& square : Squares) {
    square.P1 = square.P1 * cm;
    square.P2 = square.P2 * cm;
    square.P3 = square.P3 * cm;
    square.P4 = square.P4 * cm;
  }
}
