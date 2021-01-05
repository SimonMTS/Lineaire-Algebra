#include "CameraPerspective.hpp"

void CameraPerspective::DrawStructures(SDL2Wrapper& drawer,
                                       vector<Structure>& structures,
                                       const cVector& pos) {
  for (auto& structure : structures) {
    for (auto& component : structure.Components) {
      for (auto sqr : component.Squares) {
        // Calc position in structure
        sqr.P1 = sqr.P1 + component.Pos;
        sqr.P2 = sqr.P2 + component.Pos;
        sqr.P3 = sqr.P3 + component.Pos;
        sqr.P4 = sqr.P4 + component.Pos;

        // Set orientation
        sqr.P1 = sqr.P1 * structure.State;
        sqr.P2 = sqr.P2 * structure.State;
        sqr.P3 = sqr.P3 * structure.State;
        sqr.P4 = sqr.P4 * structure.State;

        // Calc on screen pos
        cMatrix pm = cMatrix::GetProjectionMatrix(1, 2000, 60);
        cMatrix rm = cMatrix::GetRotationMatrix(1, get<0>(Rotation)) *
                     cMatrix::GetRotationMatrix(2, get<1>(Rotation)) *
                     cMatrix::GetRotationMatrix(3, get<2>(Rotation));
        sqr.P1 = ((sqr.P1 + pos) * rm * pm);
        sqr.P2 = ((sqr.P2 + pos) * rm * pm);
        sqr.P3 = ((sqr.P3 + pos) * rm * pm);
        sqr.P4 = ((sqr.P4 + pos) * rm * pm);

        if (sqr.P1.W < 0 || sqr.P2.W < 0 || sqr.P3.W < 0 || sqr.P4.W < 0) {
          continue;
        }

        sqr.P1.X =
            (drawer.Height / 2) + ((sqr.P1.X / sqr.P1.W) * (drawer.Height / 2));
        sqr.P1.Y =
            (drawer.Height / 2) + ((sqr.P1.Y / sqr.P1.W) * (drawer.Height / 2));
        sqr.P2.X =
            (drawer.Height / 2) + ((sqr.P2.X / sqr.P2.W) * (drawer.Height / 2));
        sqr.P2.Y =
            (drawer.Height / 2) + ((sqr.P2.Y / sqr.P2.W) * (drawer.Height / 2));
        sqr.P3.X =
            (drawer.Height / 2) + ((sqr.P3.X / sqr.P3.W) * (drawer.Height / 2));
        sqr.P3.Y =
            (drawer.Height / 2) + ((sqr.P3.Y / sqr.P3.W) * (drawer.Height / 2));
        sqr.P4.X =
            (drawer.Height / 2) + ((sqr.P4.X / sqr.P4.W) * (drawer.Height / 2));
        sqr.P4.Y =
            (drawer.Height / 2) + ((sqr.P4.Y / sqr.P4.W) * (drawer.Height / 2));

        drawer.DrawSquare(sqr.P1.X, sqr.P1.Y, sqr.P2.X, sqr.P2.Y, sqr.P3.X,
                          sqr.P3.Y, sqr.P4.X, sqr.P4.Y, {0, 0, 0});
      }
    }
  }
}