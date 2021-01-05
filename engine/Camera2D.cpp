#include "Camera2D.hpp"

void Camera2D::DrawGrid(SDL2Wrapper& drawer, const cVector& pos) {
  const double GridStep = 1;

  RGB gridColor = RGB(245, 245, 245);

  RGB gridOriginColor = RGB(224, 224, 224);
  RGB colorX = RGB(255, 152, 0);
  RGB colorY = RGB(33, 150, 243);
  RGB colorZ = RGB(76, 175, 80);

  for (int x = (int)(pos.Y) % 20; x < drawer.Height; x += 20) {
    drawer.DrawLine(0, x, drawer.Width, x, gridColor);
  }
  for (int y = (int)(pos.X) % 20; y < drawer.Width; y += 20) {
    drawer.DrawLine(y, 0, y, drawer.Height, gridColor);
  }

  drawer.DrawLine(pos.X * GridStep, 0, pos.X * GridStep, drawer.Height,
                  gridOriginColor);
  drawer.DrawLine(0, pos.Y * GridStep, drawer.Width, pos.Y * GridStep,
                  gridOriginColor);
}

void Camera2D::DrawStructures(SDL2Wrapper& drawer,
                              vector<Structure>& structures,
                              const cVector& pos) {
  for (auto& structure : structures) {
    for (auto& component : structure.Components) {
      for (auto square : component.Squares) {
        {
          drawer.DrawLine(structure.Pos.X + pos.X, structure.Pos.Z + pos.Z,
                          structure.Pos.X + pos.X + (structure.Dir * 100).X,
                          structure.Pos.Z + pos.Z + (structure.Dir * 100).Z,
                          {250, 0, 0});

          square.P1 = square.P1 + component.Pos;
          square.P2 = square.P2 + component.Pos;
          square.P3 = square.P3 + component.Pos;
          square.P4 = square.P4 + component.Pos;

          // apply Dir
          {
            cVector from = {0, 0, 1};
            cVector to = structure.Dir;

            cVector distance = from - to;
            if (distance.Length() > 0.001) {
              cVector directionA = {0, 0, 1};
              cVector directionB = to;

              double rotationAngle =
                  acos(directionA.DotProduct(directionB)) * (180.0 / M_PI);
              cVector rotationAxis =
                  directionA.CrossProduct(directionB).Normalized();

              if (abs(rotationAngle) > 0.001) {
                auto rm =
                    cMatrix::GetRotationMatrix(rotationAxis, -rotationAngle);
                square.P1 = square.P1 * rm;
                square.P2 = square.P2 * rm;
                square.P3 = square.P3 * rm;
                square.P4 = square.P4 * rm;
              }
            }
          }

          // apply Rot
          auto rm = cMatrix::GetRotationMatrix(structure.Dir, structure.Rot);
          square.P1 = square.P1 * rm;
          square.P2 = square.P2 * rm;
          square.P3 = square.P3 * rm;
          square.P4 = square.P4 * rm;
        }

        double l1x = square.P1.X + pos.X + structure.Pos.X;
        double l1y = square.P1.Z + pos.Z + structure.Pos.Z;
        double l2x = square.P2.X + pos.X + structure.Pos.X;
        double l2y = square.P2.Z + pos.Z + structure.Pos.Z;

        double l3x = square.P3.X + pos.X + structure.Pos.X;
        double l3y = square.P3.Z + pos.Z + structure.Pos.Z;
        double l4x = square.P4.X + pos.X + structure.Pos.X;
        double l4y = square.P4.Z + pos.Z + structure.Pos.Z;

        drawer.DrawLine(l1x, l1y, l2x, l2y, {0, 0, 0});
        drawer.DrawLine(l1x, l1y, l3x, l3y, {0, 0, 0});
        drawer.DrawLine(l4x, l4y, l2x, l2y, {0, 0, 0});
        drawer.DrawLine(l4x, l4y, l3x, l3y, {0, 0, 0});
      }
    }
  }
}