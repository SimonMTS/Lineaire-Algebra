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
  const double GridStep = 1;
  for (auto& structure : structures) {
    // auto sOffset = structure.first;
    for (auto& component : structure.Components) {
      // auto oOffset = object.first;
      for (auto square : component.Squares) {
        {
          drawer.DrawLine(structure.Pos.X + pos.X, structure.Pos.Z + pos.Z,
                          structure.Pos.X + pos.X + (structure.Dir.X * 100),
                          structure.Pos.Z + pos.Z + (structure.Dir.Z * 100),
                          {250, 0, 0});

          auto p1 = structure.Pos;
          cVector p2 = {100, 100, 100};

          double a = 0;  // 360.0 * structure.Dir.Z;
          double n = (p1.Length() *
                    p2.Length());
          if (n != 0) {
            std::cout << acos(p1.DotProduct(p2) / n) << "\n";

            double prod = p1.DotProduct(p2);
            double asd = prod / n;
            a = acos(asd);
            a = acos(asd);
          }
          // std::cout << structure.Dir.DotProduct(structure.Pos) << "\n";
          // std::cout << structure.Dir.CrossProduct(structure.Pos) << "\n";
          // std::cout << () / () << "\n";
          // std::cout << structure.Dir.Length() << "\n\n";
          auto rm = cMatrix::GetRotationMatrix(2, 360 * a);
          square.P1 = square.P1 * rm;
          square.P2 = square.P2 * rm;
          square.P3 = square.P3 * rm;
          square.P4 = square.P4 * rm;

          //std::cout << structure.Pos.Length() << "  \r";
        }

        double l1x = square.P1.X;  // + oOffset.X + sOffset.X;
        double l1y = square.P1.Z;  // + oOffset.Z + sOffset.Z;
        double l2x = square.P2.X;  // + oOffset.X + sOffset.X;
        double l2y = square.P2.Z;  // + oOffset.Z + sOffset.Z;

        double l3x = square.P3.X;  // + oOffset.X + sOffset.X;
        double l3y = square.P3.Z;  // + oOffset.Z + sOffset.Z;
        double l4x = square.P4.X;  // + oOffset.X + sOffset.X;
        double l4y = square.P4.Z;  // + oOffset.Z + sOffset.Z;

        l1x = (l1x * GridStep) + (pos.X * GridStep) + structure.Pos.X;
        l1y = (l1y * GridStep) + (pos.Z * GridStep) + structure.Pos.Z;
        l2x = (l2x * GridStep) + (pos.X * GridStep) + structure.Pos.X;
        l2y = (l2y * GridStep) + (pos.Z * GridStep) + structure.Pos.Z;

        l3x = (l3x * GridStep) + (pos.X * GridStep) + structure.Pos.X;
        l3y = (l3y * GridStep) + (pos.Z * GridStep) + structure.Pos.Z;
        l4x = (l4x * GridStep) + (pos.X * GridStep) + structure.Pos.X;
        l4y = (l4y * GridStep) + (pos.Z * GridStep) + structure.Pos.Z;

        // Sdl.DrawLine(l1x, l1y, l2x, l2y, {0, 0, 0});
        drawer.DrawLine(l1x, l1y, l2x, l2y, {0, 0, 0});
        drawer.DrawLine(l1x, l1y, l3x, l3y, {0, 0, 0});
        drawer.DrawLine(l4x, l4y, l2x, l2y, {0, 0, 0});
        drawer.DrawLine(l4x, l4y, l3x, l3y, {0, 0, 0});
      }
    }
  }
}