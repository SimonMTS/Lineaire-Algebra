#include "Vector2D.h"

Vector2D::Vector2D(int x, int y) : X(x), Y(y) {}

Vector2D Vector2D::operator+(const Vector2D& v) {
  return Vector2D(this->X + v.X, this->Y + v.Y);
}

Vector2D Vector2D::operator-(const Vector2D& v) {
  return Vector2D(this->X - v.X, this->Y - v.Y);
}

Vector2D Vector2D::operator*(int i) {
  return Vector2D(this->X * i, this->Y * i);
}