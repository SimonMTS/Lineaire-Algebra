#include "Structure.h"

void Structure::AddObject(pair<Point3D, Object>& o) {
  Objects.push_back(o); }

void Structure::Scale(const double x, const double y, const double z) {}

void Structure::Move(const double x, const double y, const double z) {}

void Structure::Rotate(const int dir) {
  for (auto& object : Objects) {
    Point3D localOrigin = Point3D{0, 0, 0} - object.first;

    Matrix3D tm1 = Matrix3D::GetTranslationMatrix(
        -localOrigin.X, -localOrigin.Y, -localOrigin.Z);
    Matrix3D tm2 = Matrix3D::GetTranslationMatrix(localOrigin.X, localOrigin.Y,
                                                  localOrigin.Z);
    Matrix3D rm = Matrix3D::GetRotationMatrix(abs(dir), (dir > 0 ? 1 : -1));
    Matrix3D cm = tm2 * rm * tm1;

    for (auto& square : object.second.Squares) {
      square.P1 = square.P1 * cm;
      square.P2 = square.P2 * cm;
      square.P3 = square.P3 * cm;
      square.P4 = square.P4 * cm;
    }
  }
}
