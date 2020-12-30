#include "Object.h"

void Object::AddLine(Line3D& l) {
  Lines.push_back(l); }

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

  for (auto& line : Lines) {
    line.P1 = line.P1 * cm;
    line.P2 = line.P2 * cm;
  }
}
