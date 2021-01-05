#include "CameraPerspective.hpp"

void CameraPerspective::DrawStructures(SDL2Wrapper& drawer,
                                       vector<Structure>& structures,
                                       const cVector& pos) {
  for (auto& structure : structures) {
    for (auto& component : structure.Components) {
      for (auto square : component.Squares) {
        // Calc real position
        square.P1 = square.P1 + component.Pos + structure.Pos;
        square.P2 = square.P2 + component.Pos + structure.Pos;
        square.P3 = square.P3 + component.Pos + structure.Pos;
        square.P4 = square.P4 + component.Pos + structure.Pos;

        // Calc on screen pos
        cMatrix pm = cMatrix::GetProjectionMatrix(1, 2000, 60);
        cMatrix rm = cMatrix::GetRotationMatrix(1, get<0>(Rotation)) *
                     cMatrix::GetRotationMatrix(2, get<1>(Rotation)) *
                     cMatrix::GetRotationMatrix(3, get<2>(Rotation));
        square.P1 = ((square.P1 + pos) * rm * pm);
        square.P2 = ((square.P2 + pos) * rm * pm);
        square.P3 = ((square.P3 + pos) * rm * pm);
        square.P4 = ((square.P4 + pos) * rm * pm);

        if (square.P1.W < 0 || square.P2.W < 0 || square.P3.W < 0 ||
            square.P4.W < 0) {
          continue;
        }

        square.P1.X = (drawer.Height / 2) + ((square.P1.X / square.P1.W) * (drawer.Height / 2));
        square.P1.Y = (drawer.Height / 2) + ((square.P1.Y / square.P1.W) * (drawer.Height / 2));
        square.P2.X = (drawer.Height / 2) + ((square.P2.X / square.P2.W) * (drawer.Height / 2));
        square.P2.Y = (drawer.Height / 2) + ((square.P2.Y / square.P2.W) * (drawer.Height / 2));
        square.P3.X = (drawer.Height / 2) + ((square.P3.X / square.P3.W) * (drawer.Height / 2));
        square.P3.Y = (drawer.Height / 2) + ((square.P3.Y / square.P3.W) * (drawer.Height / 2));
        square.P4.X = (drawer.Height / 2) + ((square.P4.X / square.P4.W) * (drawer.Height / 2));
        square.P4.Y = (drawer.Height / 2) + ((square.P4.Y / square.P4.W) * (drawer.Height / 2));

        drawer.DrawSquare(square.P1.X, square.P1.Y, square.P2.X, square.P2.Y,
                          square.P3.X, square.P3.Y, square.P4.X, square.P4.Y,
                          {0, 0, 0});
      }
    }
  }
}