#include "Component.hpp"

void Component::AddSquare(const Square& s) { Squares.push_back(s); }

void Component::operator*=(const cMatrix& m) {
  for (auto& square : Squares) {
    square.P1 = square.P1 * m;
    square.P2 = square.P2 * m;
    square.P3 = square.P3 * m;
    square.P4 = square.P4 * m;
  }
}
