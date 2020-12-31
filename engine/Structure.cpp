#include "Structure.hpp"

void Structure::AddComponent(const Component& c) { Components.push_back(c); }

void Structure::operator*=(const cMatrix& m) {
  for (auto& component : Components) {

    for (auto& square : component.Squares) {
      square.P1 = square.P1 * m;
      square.P2 = square.P2 * m;
      square.P3 = square.P3 * m;
      square.P4 = square.P4 * m;
    }
  }
}
