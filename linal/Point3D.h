#pragma once
#include "Matrix3D.h"

class Point3D {
public:
    double X;
    double Y;
    double Z;
    double W = 1;

    Point3D(double x, double y, double z);

    Point3D operator*(Matrix3D m);
    Point3D operator+(Matrix3D m);
};

