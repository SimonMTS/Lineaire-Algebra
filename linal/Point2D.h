#pragma once
#include "Matrix2D.h"

class Point2D {
public:
    double X;
    double Y;
    double W = 1;

    Point2D(const double x, const double y);

    Point2D operator*(Matrix2D m);
    Point2D operator+(Matrix2D m);
};
