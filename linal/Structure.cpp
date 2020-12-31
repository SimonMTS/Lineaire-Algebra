#include "Structure.h"
#include <iostream>

void Structure::AddObject(pair<Point3D, Object>& o) { Objects.push_back(o); }

void Structure::Scale(const double x, const double y, const double z) {
  for (auto& object : Objects) {
    Point3D localOrigin = Point3D{0, 0, 0} - object.first;

    Matrix3D tm1 = Matrix3D::GetTranslationMatrix(
        -localOrigin.X, -localOrigin.Y, -localOrigin.Z);
    Matrix3D tm2 = Matrix3D::GetTranslationMatrix(localOrigin.X, localOrigin.Y,
                                                  localOrigin.Z);
    Matrix3D sm = Matrix3D::GetScalingMatrix(x, y, z);
    Matrix3D cm = tm2 * sm * tm1;

    for (auto& square : object.second.Squares) {
      square.P1 = square.P1 * cm;
      square.P2 = square.P2 * cm;
      square.P3 = square.P3 * cm;
      square.P4 = square.P4 * cm;
    }
  }
}

void Structure::Move(const double x, const double y, const double z) {
  for (auto& object : Objects) {
    Point3D localOrigin = Point3D{0, 0, 0} - object.first;

    Matrix3D tm = Matrix3D::GetTranslationMatrix(x, y, z);

    for (auto& square : object.second.Squares) {
      square.P1 = square.P1 * tm;
      square.P2 = square.P2 * tm;
      square.P3 = square.P3 * tm;
      square.P4 = square.P4 * tm;
    }
  }
}

void Structure::Rotate(const int dir, const int angle) {

  //switch (abs(dir)) {
  //  case 1:
  //    Rot1 = Rot1 * rm;
  //    break;
  //  case 2:
  //    Rot2 = Rot2 * rm;
  //    break;
  //  case 3:
  //    Rot3 = Rot3 * rm;
  //    break;
  //}

  for (auto& object : Objects) {
    Point3D localOrigin = Point3D{0, 0, 0} - object.first;

    Matrix3D tm1 = Matrix3D::GetTranslationMatrix(
        -localOrigin.X, -localOrigin.Y, -localOrigin.Z);
    Matrix3D tm2 = Matrix3D::GetTranslationMatrix(localOrigin.X, localOrigin.Y,
                                                  localOrigin.Z);
    Matrix3D rm = Matrix3D::GetRotationMatrix(abs(dir), angle);
    Matrix3D cm = tm2 * rm * tm1;
    Rot = rm * Rot;

    for (auto& square : object.second.Squares) {
      square.P1 = square.P1 * cm;
      square.P2 = square.P2 * cm;
      square.P3 = square.P3 * cm;
      square.P4 = square.P4 * cm;
    }
  }
}
