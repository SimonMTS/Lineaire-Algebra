#include "Camera2D.hpp"

void Camera2D::DrawGrid(SDL2Wrapper& drawer, bool dark_mode) {
  RGB gridColor = dark_mode ? RGB(42, 42, 42) : RGB(245, 245, 245);
  RGB gridOriginColor = dark_mode ? RGB(61, 61, 61) : RGB(224, 224, 224);

  for (int x = (int)(State[2][3]) % 20; x < drawer.Height; x += 20) {
    drawer.DrawLine(0, x, drawer.Width, x, gridColor);
  }
  for (int y = (int)(-State[0][3]) % 20; y < drawer.Width; y += 20) {
    drawer.DrawLine(y, 0, y, drawer.Height, gridColor);
  }

  drawer.DrawLine(-State[0][3], 0, -State[0][3], drawer.Height,
                  gridOriginColor);
  drawer.DrawLine(0, State[2][3], drawer.Width, State[2][3], gridOriginColor);
}

void Camera2D::DrawStructures(SDL2Wrapper& drawer,
                              vector<Structure>& structures,
                              vector<unique_ptr<Camera>>& cameras,
                              bool dark_mode) {
  for (auto& structure : structures) {
    for (auto& component : structure.Components) {
      for (auto sqr : component.Squares) {
        // Calc position in structure
        sqr.P1 += component.Pos;
        sqr.P2 += component.Pos;
        sqr.P3 += component.Pos;
        sqr.P4 += component.Pos;

        // Set orientation
        sqr.P1 = (sqr.P1 * structure.State) +
                 cVector(State[0][3], State[1][3], State[2][3]);
        sqr.P2 = (sqr.P2 * structure.State) +
                 cVector(State[0][3], State[1][3], State[2][3]);
        sqr.P3 = (sqr.P3 * structure.State) +
                 cVector(State[0][3], State[1][3], State[2][3]);
        sqr.P4 = (sqr.P4 * structure.State) +
                 cVector(State[0][3], State[1][3], State[2][3]);

        // Set top view
        auto rm = cMatrix::GetRotationMatrix({0, 0, 1}, 180);
        sqr.P1 *= rm;
        sqr.P2 *= rm;
        sqr.P3 *= rm;
        sqr.P4 *= rm;

        // Draw square
        RGB color = dark_mode ? RGB(250, 250, 250) : RGB(21, 21, 21);
        drawer.DrawLine(sqr.P1.X, sqr.P1.Z, sqr.P2.X, sqr.P2.Z, color);
        drawer.DrawLine(sqr.P1.X, sqr.P1.Z, sqr.P3.X, sqr.P3.Z, color);
        drawer.DrawLine(sqr.P4.X, sqr.P4.Z, sqr.P2.X, sqr.P2.Z, color);
        drawer.DrawLine(sqr.P4.X, sqr.P4.Z, sqr.P3.X, sqr.P3.Z, color);
      }
    }
  }

  // Draw helpline
  if (Renderer::show_helpline && structures.size() == 1 &&
      structures.at(0).Components.size() > 4) {
    cVector camOffset = {-State[0][3], State[1][3], State[2][3]};

    cVector origin = {0, 0, 25};
    origin *= structures.at(0).State;
    origin *= cMatrix::GetRotationMatrix({0, 0, 1}, 180);

    const double len = 2000;

    cVector dir = {0, 0, len};
    dir *= structures.at(0).State;
    dir *= cMatrix::GetRotationMatrix({0, 0, 1}, 180);
    drawer.DrawLine(origin.X + camOffset.X, origin.Z + camOffset.Z,
                    dir.X + camOffset.X, dir.Z + camOffset.Z, {100, 255, 100});
  }

  // Draw direction
  if (Renderer::show_orientation) {
    for (auto& structure : structures) {
      cVector camOffset = {-State[0][3], State[1][3], State[2][3]};

      cVector origin = {0, 0, 0};
      origin *= structure.State;
      origin *= cMatrix::GetRotationMatrix({0, 0, 1}, 180);

      const double len = 50;

      // Forward
      {
        cVector dir = {0, 0, len};
        dir *= structure.State;
        dir *= cMatrix::GetRotationMatrix({0, 0, 1}, 180);
        drawer.DrawLine(origin.X + camOffset.X, origin.Z + camOffset.Z,
                        dir.X + camOffset.X, dir.Z + camOffset.Z, {250, 0, 0});
      }

      // Up
      {
        cVector dir = {0, len, 0};
        dir *= structure.State;
        dir *= cMatrix::GetRotationMatrix({0, 0, 1}, 180);
        drawer.DrawLine(origin.X + camOffset.X, origin.Z + camOffset.Z,
                        dir.X + camOffset.X, dir.Z + camOffset.Z, {0, 250, 0});
      }

      // Side
      {
        cVector dir = {len, 0, 0};
        dir *= structure.State;
        dir *= cMatrix::GetRotationMatrix({0, 0, 1}, 180);
        drawer.DrawLine(origin.X + camOffset.X, origin.Z + camOffset.Z,
                        dir.X + camOffset.X, dir.Z + camOffset.Z, {0, 0, 250});
      }
    }
  }

  // Draw Cameras
  if (Renderer::show_camera_orientation) {
    for (auto& camera : cameras) {
      if (camera.get() == this) continue;

      auto camState = camera->State;
      camState *= cMatrix::GetRotationMatrix({0, 0, 1}, 180);

      cVector camOffset = {-State[0][3], State[1][3], State[2][3]};

      cVector origin = {0, 0, 0};
      origin *= camState;

      const double len = 50;

      // Forward
      {
        cVector dir = {0, 0, len};
        dir *= camState;
        drawer.DrawLine(origin.X + camOffset.X, origin.Z + camOffset.Z,
                        dir.X + camOffset.X, dir.Z + camOffset.Z, {250, 0, 0});
      }

      // Up
      {
        cVector dir = {0, len / 2, 0};
        dir *= camState;
        drawer.DrawLine(origin.X + camOffset.X, origin.Z + camOffset.Z,
                        dir.X + camOffset.X, dir.Z + camOffset.Z, {0, 250, 0});
      }

      // Side
      {
        cVector dir = {len / 2, 0, 0};
        dir *= camState;
        drawer.DrawLine(origin.X + camOffset.X, origin.Z + camOffset.Z,
                        dir.X + camOffset.X, dir.Z + camOffset.Z, {0, 0, 250});
      }
    }
  }

  // Draw AABB
  if (Renderer::show_AABB) {
    for (auto& structure : structures) {
      auto AABB = structure.AABB;

      cVector origin = {0, 0, 0};
      {
        origin *= cMatrix::TranslationOnly(structure.State);
        origin *= cMatrix::GetRotationMatrix({0, 0, 1}, 180);

        cVector camOffset = {-State[0][3], State[1][3], State[2][3]};
        origin += camOffset;
      }

      RGB col =
          structure.WasCollidingLastCheck ? RGB{255, 0, 0} : RGB{0, 0, 255};

      drawer.DrawSquare(origin.X - AABB[0], origin.Z + AABB[2],
                        origin.X - AABB[0], origin.Z + AABB[5],
                        origin.X - AABB[3], origin.Z + AABB[2],
                        origin.X - AABB[3], origin.Z + AABB[5], col);
    }
  }
}

void Camera2D::HandleMouseEvent(const int type, const int d1, const int d2) {
  // Mouse down
  if (type == 1025) {
    IsDragging = {true, d1, d2};
  }
  // Mouse up
  if (type == 1026) {
    IsDragging = {false, 0, 0};
  }
  if (type == 1024 && get<0>(IsDragging)) {
    State[0][3] += (double)get<1>(IsDragging) - (double)d1;
    State[2][3] += (double)get<2>(IsDragging) - (double)d2;
    IsDragging = {true, d1, d2};
  }
}
