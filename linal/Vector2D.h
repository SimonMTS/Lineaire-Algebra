#pragma once

class Vector2D {
 public:
  int X;
  int Y;

  Vector2D(int x, int y);

  Vector2D operator+(const Vector2D& v);
  Vector2D operator-(const Vector2D& v);
  Vector2D operator*(int v);
};
