#include "CameraPerspective.hpp"

void CameraPerspective::DrawStructures(SDL2Wrapper& drawer,
                                       vector<Structure>& structures,
                                       const cVector& pos) {
  for (auto& structure : structures) {
    for (auto& component : structure.Components) {
      for (auto square : component.Squares) {
        {
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

        square.P1 = square.P1 + structure.Pos;
        square.P2 = square.P2 + structure.Pos;
        square.P3 = square.P3 + structure.Pos;
        square.P4 = square.P4 + structure.Pos;

        cMatrix pm = cMatrix::GetProjectionMatrix(1, 200, 60);
        cMatrix rm = cMatrix::GetRotationMatrix(1, get<0>(Rotation)) *
                     cMatrix::GetRotationMatrix(2, get<1>(Rotation)) *
                     cMatrix::GetRotationMatrix(3, get<2>(Rotation));

        square.P1 = square.P1 * rm * pm;
        square.P2 = square.P2 * rm * pm;
        square.P3 = square.P3 * rm * pm;
        square.P4 = square.P4 * rm * pm;

        {
          cVector asd = structure.Pos + pos;

          //std::cout << structure.Pos << "\n";
          drawer.DrawLine(asd.X, asd.Z, asd.X + (structure.Dir * 100).X,
                          asd.Z + (structure.Dir * 100).Z, {250, 0, 0});
        }

        if (square.P1.W < 0 || square.P2.W < 0 || square.P3.W < 0 ||
            square.P4.W < 0) {
          continue;
        }

        drawer.DrawSquare(square.P1.X, square.P1.Y, square.P2.X, square.P2.Y,
                          square.P3.X, square.P3.Y, square.P4.X, square.P4.Y,
                          {0, 0, 0});
      }
    }
  }
  /*for (auto& structure : structures) {
    for (auto& object : structure.Components) {
      for (auto& square : object.Squares) {
        cVector p1 = square.P1;
        {
          p1.X += -pos.X;// + oOffset.X + sOffset.X;
          p1.Y += -pos.Y;// + oOffset.Y + sOffset.Y;
          p1.Z += -pos.Z;// + oOffset.Z + sOffset.Z;
        }
        cVector p2 = square.P2;
        {
          p2.X += -pos.X;  // + oOffset.X + sOffset.X;
          p2.Y += -pos.Y;  // + oOffset.Y + sOffset.Y;
          p2.Z += -pos.Z;  // + oOffset.Z + sOffset.Z;
        }
        cVector p3 = square.P3;
        {
          p3.X += -pos.X;  // + oOffset.X + sOffset.X;
          p3.Y += -pos.Y;  // + oOffset.Y + sOffset.Y;
          p3.Z += -pos.Z;  // + oOffset.Z + sOffset.Z;
        }
        cVector p4 = square.P4;
        {
          p4.X += -pos.X;  // + oOffset.X + sOffset.X;
          p4.Y += -pos.Y;  // + oOffset.Y + sOffset.Y;
          p4.Z += -pos.Z;  // + oOffset.Z + sOffset.Z;
        }

        cMatrix pm = cMatrix::GetProjectionMatrix(1, 200, 60);
        cMatrix rm = cMatrix::GetRotationMatrix(1, get<0>(Rotation)) *
                     cMatrix::GetRotationMatrix(2, get<1>(Rotation)) *
                     cMatrix::GetRotationMatrix(3, get<2>(Rotation));

        p1 = p1 * rm * pm;
        p2 = p2 * rm * pm;
        p3 = p3 * rm * pm;
        p4 = p4 * rm * pm;

        p1.X = (drawer.Width / 2) + ((p1.X / p1.W) * (drawer.Width / 2));
        p1.Y = (drawer.Width / 2) + ((p1.Y / p1.W) * (drawer.Width / 2));

        p2.X = (drawer.Width / 2) + ((p2.X / p2.W) * (drawer.Width / 2));
        p2.Y = (drawer.Width / 2) + ((p2.Y / p2.W) * (drawer.Width / 2));

        p3.X = (drawer.Width / 2) + ((p3.X / p3.W) * (drawer.Width / 2));
        p3.Y = (drawer.Width / 2) + ((p3.Y / p3.W) * (drawer.Width / 2));

        p4.X = (drawer.Width / 2) + ((p4.X / p4.W) * (drawer.Width / 2));
        p4.Y = (drawer.Width / 2) + ((p4.Y / p4.W) * (drawer.Width / 2));

        // drawer.DrawLine(p1.X, p1.Y, p2.X, p2.Y, color);
        // drawer.DrawLine(p1.X, p1.Y, p3.X, p3.Y, color);
        // drawer.DrawLine(p4.X, p4.Y, p2.X, p2.Y, color);
        // drawer.DrawLine(p4.X, p4.Y, p3.X, p3.Y, color);

        if (p1.W < 0 || p2.W < 0 || p3.W < 0 || p4.W < 0) continue;

        drawer.DrawSquare(p1.X, p1.Y, p2.X, p2.Y, p3.X, p3.Y, p4.X, p4.Y,
                       {0, 0, 0});
      }
    }
  }*/
}