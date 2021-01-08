#include "Structure.hpp"

void Structure::AddComponent(const Component& c) { Components.push_back(c); }

void Structure::RegisterPerTickAction(
    const function<void(const int tick, Structure& structure, Renderer& r)>&
        callback) {
  PerTickAction = callback;
}

void Structure::ExecutePerTickAction(const int tick, Renderer& r) {
  if (PerTickAction) PerTickAction(tick, *this, r);
}

void Structure::operator*=(const cMatrix& m) {
  for (auto& comp : Components) {
    for (auto& square : comp.Squares) {
      square.P1 = ((square.P1 + comp.Pos) * m) - comp.Pos;
      square.P2 = ((square.P2 + comp.Pos) * m) - comp.Pos;
      square.P3 = ((square.P3 + comp.Pos) * m) - comp.Pos;
      square.P4 = ((square.P4 + comp.Pos) * m) - comp.Pos;
    }
  }
}
