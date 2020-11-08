#include "Point2D.h"

Point2D::Point2D(const double x, const double y) : X(x), Y(y) { }

Point2D Point2D::operator*(Matrix2D m) {
    Point2D p(this->X, this->Y);
	p.X = m[0][0] * this->X + m[0][1] * this->Y + m[0][2] * this->W;
	p.Y = m[1][0] * this->X + m[1][1] * this->Y + m[1][2] * this->W;
    p.W = m[2][0] * this->X + m[2][1] * this->Y + m[2][2] * this->W;

    return p;
}

Point2D Point2D::operator+(Matrix2D m) {
    Point2D p(this->X, this->Y);
    p.X = m[0][0] + p.X + m[0][1] + p.Y;
    p.Y = m[1][0] + p.X + m[1][1] + p.Y;

    return p;
}