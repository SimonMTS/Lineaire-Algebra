#pragma once
#include "Matrix3D.h"
#include <ostream>
using std::ostream;

class Point3D {
public:
    double X;
    double Y;
    double Z;
    double W = 1;

    Point3D(double x, double y, double z);

    int InProduct(Point3D other);
    Point3D OutProduct(Point3D other);

    Point3D operator*(Matrix3D m);
    Point3D operator+(Matrix3D m);
};

ostream& operator<<(ostream& Str, Point3D p);