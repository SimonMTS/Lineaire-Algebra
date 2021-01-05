#include "Camera2D.hpp"

void Camera2D::DrawGrid(SDL2Wrapper& drawer, const cVector& pos) {
  const double GridStep = 1;

  RGB gridColor = RGB(245, 245, 245);

  RGB gridOriginColor = RGB(224, 224, 224);
  RGB colorX = RGB(255, 152, 0);
  RGB colorY = RGB(33, 150, 243);
  RGB colorZ = RGB(76, 175, 80);

  for (int x = (int)(pos.Z) % 20; x < drawer.Height; x += 20) {
    drawer.DrawLine(0, x, drawer.Width, x, gridColor);
  }
  for (int y = (int)(pos.X) % 20; y < drawer.Width; y += 20) {
    drawer.DrawLine(y, 0, y, drawer.Height, gridColor);
  }

  drawer.DrawLine(pos.X * GridStep, 0, pos.X * GridStep, drawer.Height,
                  gridOriginColor);
  drawer.DrawLine(0, pos.Z * GridStep, drawer.Width, pos.Z * GridStep,
                  gridOriginColor);
}

void Camera2D::DrawStructures(SDL2Wrapper& drawer,
                              vector<Structure>& structures,
                              const cVector& pos) {
  for (auto& structure : structures) {
    // Structure direction
    // drawer.DrawLine(structure.Pos.X + pos.X, structure.Pos.Z + pos.Z,
    //                structure.Pos.X + pos.X + (structure.Dir * 100).X,
    //                structure.Pos.Z + pos.Z + (structure.Dir * 100).Z,
    //                {250, 0, 0});

    for (auto& component : structure.Components) {
      for (auto sqr : component.Squares) {
        // Calc position in structure
        sqr.P1 = sqr.P1 + component.Pos;
        sqr.P2 = sqr.P2 + component.Pos;
        sqr.P3 = sqr.P3 + component.Pos;
        sqr.P4 = sqr.P4 + component.Pos;

        // Set orientation
        sqr.P1 = (sqr.P1 * structure.State) + pos;
        sqr.P2 = (sqr.P2 * structure.State) + pos;
        sqr.P3 = (sqr.P3 * structure.State) + pos;
        sqr.P4 = (sqr.P4 * structure.State) + pos;

        // Draw square
        drawer.DrawLine(sqr.P1.X, sqr.P1.Z, sqr.P2.X, sqr.P2.Z, {0, 0, 0});
        drawer.DrawLine(sqr.P1.X, sqr.P1.Z, sqr.P3.X, sqr.P3.Z, {0, 0, 0});
        drawer.DrawLine(sqr.P4.X, sqr.P4.Z, sqr.P2.X, sqr.P2.Z, {0, 0, 0});
        drawer.DrawLine(sqr.P4.X, sqr.P4.Z, sqr.P3.X, sqr.P3.Z, {0, 0, 0});
      }
    }
  }
}

cVector Camera2D::HandleMouseEvent(const int type, const int d1, const int d2) {
  // Mouse down
  if (type == 1025) {
    std::cout << "\ndrag start\n";
    IsDragging = {true, d1, d2};
  }
  // Mouse up
  if (type == 1026) {
    std::cout << "\ndrag end\n";
    IsDragging = {false, 0, 0};
  }
  if (type == 1024 && get<0>(IsDragging)) {
    double delta_x = (double)get<1>(IsDragging) - (double)d1;
    double delta_z = (double)get<2>(IsDragging) - (double)d2;
    IsDragging = {true, d1, d2};
    return {-delta_x, 0, delta_z};
  }

  return {0, 0, 0};
}
