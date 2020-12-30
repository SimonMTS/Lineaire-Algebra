#include "Camera2D.h"

void Camera2D::DrawGrid(SDL2Wrapper& Sdl, Point3D& pos) {
  const double GridStep = 1;

  RGB gridColor = RGB(245, 245, 245);

  RGB gridOriginColor = RGB(224, 224, 224);
  RGB colorX = RGB(255, 152, 0);
  RGB colorY = RGB(33, 150, 243);
  RGB colorZ = RGB(76, 175, 80);

  for (int x = (int)(pos.Y) % 20; x < Sdl.Height; x += 20) {
    Sdl.DrawLine(0, x, Sdl.Width, x, gridColor);
  }
  for (int y = (int)(pos.X) % 20; y < Sdl.Width; y += 20) {
    Sdl.DrawLine(y, 0, y, Sdl.Height, gridColor);
  }
  Sdl.DrawLine(pos.X * GridStep, 0, pos.X * GridStep, Sdl.Height, gridOriginColor);
  Sdl.DrawLine(0, pos.Y * GridStep, Sdl.Width, pos.Y * GridStep, gridOriginColor);
}

void Camera2D::DrawStructures(SDL2Wrapper& Sdl,
                              vector<pair<Point3D, Structure>>& Structures,
                              Point3D& pos) {
  const double GridStep = 1;
  for (auto& structure : Structures) {
    auto sOffset = structure.first;
    for (auto& object : structure.second.Objects) {
      auto oOffset = object.first;
      for (auto& line : object.second.Squares) {
        double l1x = line.P1.X + oOffset.X + sOffset.X;
        double l1y = line.P1.Z + oOffset.Z + sOffset.Z;
        double l2x = line.P2.X + oOffset.X + sOffset.X;
        double l2y = line.P2.Z + oOffset.Z + sOffset.Z;

        double l3x = line.P3.X + oOffset.X + sOffset.X;
        double l3y = line.P3.Z + oOffset.Z + sOffset.Z;
        double l4x = line.P4.X + oOffset.X + sOffset.X;
        double l4y = line.P4.Z + oOffset.Z + sOffset.Z;

        l1x = (l1x * GridStep) + (pos.X * GridStep);
        l1y = (l1y * GridStep) + (pos.Y * GridStep);
        l2x = (l2x * GridStep) + (pos.X * GridStep);
        l2y = (l2y * GridStep) + (pos.Y * GridStep);

        l3x = (l3x * GridStep) + (pos.X * GridStep);
        l3y = (l3y * GridStep) + (pos.Y * GridStep);
        l4x = (l4x * GridStep) + (pos.X * GridStep);
        l4y = (l4y * GridStep) + (pos.Y * GridStep);

        //Sdl.DrawLine(l1x, l1y, l2x, l2y, {0, 0, 0});
        Sdl.DrawLine(l1x, l1y, l2x, l2y, {0, 0, 0});
        Sdl.DrawLine(l1x, l1y, l3x, l3y, {0, 0, 0});
        Sdl.DrawLine(l4x, l4y, l2x, l2y, {0, 0, 0});
        Sdl.DrawLine(l4x, l4y, l3x, l3y, {0, 0, 0});
      }
    }
  }
}