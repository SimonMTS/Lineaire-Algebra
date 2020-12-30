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
      for (auto& line : object.second.Lines) {
        double startFrameX = line.P1.X + oOffset.X + sOffset.X;
        double startFrameY = line.P1.Z + oOffset.Z + sOffset.Z;
        double endFrameX = line.P2.X + oOffset.X + sOffset.X;
        double endFrameY = line.P2.Z + oOffset.Z + sOffset.Z;
        RGB color = RGB(0, 0, 0);

        startFrameX = (startFrameX * GridStep) + (pos.X * GridStep);
        startFrameY = (startFrameY * GridStep) + (pos.Y * GridStep);
        endFrameX = (endFrameX * GridStep) + (pos.X * GridStep);
        endFrameY = (endFrameY * GridStep) + (pos.Y * GridStep);

        Sdl.DrawLine(startFrameX, startFrameY, endFrameX, endFrameY, color);
      }
    }
  }
}