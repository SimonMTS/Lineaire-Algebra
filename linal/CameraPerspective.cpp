#include "CameraPerspective.h"

void CameraPerspective::DrawGrid(SDL2Wrapper& Sdl, Point3D& pos) {}

void CameraPerspective::DrawStructures(
    SDL2Wrapper& Sdl, vector<pair<Point3D, Structure>>& Structures,
    Point3D& pos) {
  for (auto& structure : Structures) {
    auto sOffset = structure.first;
    for (auto& object : structure.second.Objects) {
      auto oOffset = object.first;
      for (auto& line : object.second.Squares) {
        Point3D p1 = line.P1;
        {
          p1.X += -pos.X + oOffset.X + sOffset.X;
          p1.Y += -pos.Y + oOffset.Y + sOffset.Y;
          p1.Z += -pos.Z + oOffset.Z + sOffset.Z;
        }
        Point3D p2 = line.P2;
        {
          p2.X += -pos.X + oOffset.X + sOffset.X;
          p2.Y += -pos.Y + oOffset.Y + sOffset.Y;
          p2.Z += -pos.Z + oOffset.Z + sOffset.Z;
        }
        Point3D p3 = line.P3;
        {
          p3.X += -pos.X + oOffset.X + sOffset.X;
          p3.Y += -pos.Y + oOffset.Y + sOffset.Y;
          p3.Z += -pos.Z + oOffset.Z + sOffset.Z;
        }
        Point3D p4 = line.P4;
        {
          p4.X += -pos.X + oOffset.X + sOffset.X;
          p4.Y += -pos.Y + oOffset.Y + sOffset.Y;
          p4.Z += -pos.Z + oOffset.Z + sOffset.Z;
        }


        Matrix3D pm = Matrix3D::GetProjectionMatrix(1, 200, 60);
        Matrix3D rm = Matrix3D::GetRotationMatrix(1, get<0>(Rotation)) *
                      Matrix3D::GetRotationMatrix(2, get<1>(Rotation)) *
                      Matrix3D::GetRotationMatrix(3, get<2>(Rotation));

        p1 = p1 * rm * pm;
        p2 = p2 * rm * pm;
        p3 = p3 * rm * pm;
        p4 = p4 * rm * pm;

        p1.X = (Sdl.Width / 2) + ((p1.X / p1.W) * (Sdl.Width / 2));
        p1.Y = (Sdl.Width / 2) + ((p1.Y / p1.W) * (Sdl.Width / 2));

        p2.X = (Sdl.Width / 2) + ((p2.X / p2.W) * (Sdl.Width / 2));
        p2.Y = (Sdl.Width / 2) + ((p2.Y / p2.W) * (Sdl.Width / 2));

        p3.X = (Sdl.Width / 2) + ((p3.X / p3.W) * (Sdl.Width / 2));
        p3.Y = (Sdl.Width / 2) + ((p3.Y / p3.W) * (Sdl.Width / 2));

        p4.X = (Sdl.Width / 2) + ((p4.X / p4.W) * (Sdl.Width / 2));
        p4.Y = (Sdl.Width / 2) + ((p4.Y / p4.W) * (Sdl.Width / 2));

        //Sdl.DrawLine(p1.X, p1.Y, p2.X, p2.Y, color);
        //Sdl.DrawLine(p1.X, p1.Y, p3.X, p3.Y, color);
        //Sdl.DrawLine(p4.X, p4.Y, p2.X, p2.Y, color);
        //Sdl.DrawLine(p4.X, p4.Y, p3.X, p3.Y, color);

        if (p1.W < 0 || p2.W < 0 || p3.W < 0 || p4.W < 0) continue;

        Sdl.DrawSquare(p1.X, p1.Y, 
                       p2.X, p2.Y, 
                       p3.X, p3.Y, 
                       p4.X, p4.Y, {0, 0, 0});
      }
    }
  }
}

void CameraPerspective::KeyPassthrough(int event, int key,
                                       std::string& rendEng) {
  if (event == SDL_KEYDOWN && key == SDL_SCANCODE_W) {
    //rendEng.Structures.at(1).second.Rotate(1, 1);
    //rendEng.Structures.at(1).second.Rotate(2, 1);
    //rendEng.Structures.at(1).second.Rotate(3, 1);
  }
}

void CameraPerspective::MousePassthrough(int event, int x, int y,
                                         std::string& rendEng) {
  if (event == SDL_MOUSEMOTION) {
    //get<0>(Rotation) = (y - 300) / 1;
    //get<1>(Rotation) = -((x - 300) / 1);
    //std::cout << get<0>(Rotation) << "deg ";
    //std::cout << get<1>(Rotation) << "deg ";
    //std::cout << get<2>(Rotation) << "deg    \r";
  }
}
