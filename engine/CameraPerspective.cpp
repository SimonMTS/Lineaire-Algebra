#include "CameraPerspective.hpp"

void CameraPerspective::DrawStructures(SDL2Wrapper& drawer,
                                       vector<Structure>& structures,
                                       vector<unique_ptr<Camera>>& cameras) {
  for (auto& structure : structures) {
    for (auto& component : structure.Components) {
      for (auto square : component.Squares) {
        // Calc position in structure
        square.P1 += component.Pos;
        square.P2 += component.Pos;
        square.P3 += component.Pos;
        square.P4 += component.Pos;

        // Apply state
        square.P1 *= structure.State;
        square.P2 *= structure.State;
        square.P3 *= structure.State;
        square.P4 *= structure.State;

        // Calc on screen pos
        cMatrix appliedState = State;

        // seems to work for cam1, atleast
        appliedState = cMatrix::RotationInverse(appliedState);
        appliedState *= cMatrix::GetRotationMatrix({0, 1, 0}, 180);
        appliedState *= cMatrix::GetRotationMatrix({0, 0, 1}, 180);

        // appliedState = cMatrix::Inverse(appliedState);
        // appliedState *= cMatrix::GetRotationMatrix({1, 0, 0}, 180);
        // appliedState = cMatrix::TranslationInverse(appliedState);

        cMatrix pm = cMatrix::GetProjectionMatrix(1, 2000, 60) * appliedState;
        square.P1 *= pm;
        square.P2 *= pm;
        square.P3 *= pm;
        square.P4 *= pm;

        if (square.P1.W < 0 || square.P2.W < 0 || square.P3.W < 0 ||
            square.P4.W < 0) {
          continue;
        }

        auto& d = drawer;
        auto& s = square;
        int ro = +((drawer.Width - drawer.Height) / 2);

        s.P1.X = (d.Height / 2) + ((s.P1.X / s.P1.W) * (d.Height / 2)) + ro;
        s.P1.Y = (d.Height / 2) + ((s.P1.Y / s.P1.W) * (d.Height / 2));
        s.P2.X = (d.Height / 2) + ((s.P2.X / s.P2.W) * (d.Height / 2)) + ro;
        s.P2.Y = (d.Height / 2) + ((s.P2.Y / s.P2.W) * (d.Height / 2));
        s.P3.X = (d.Height / 2) + ((s.P3.X / s.P3.W) * (d.Height / 2)) + ro;
        s.P3.Y = (d.Height / 2) + ((s.P3.Y / s.P3.W) * (d.Height / 2));
        s.P4.X = (d.Height / 2) + ((s.P4.X / s.P4.W) * (d.Height / 2)) + ro;
        s.P4.Y = (d.Height / 2) + ((s.P4.Y / s.P4.W) * (d.Height / 2));

        drawer.DrawSquare(s.P1.X, s.P1.Y, s.P2.X, s.P2.Y, s.P3.X, s.P3.Y,
                          s.P4.X, s.P4.Y, {21, 21, 21});
      }
    }
  }

  // Draw AABB
  for (auto& structure : structures) {
    structure.CalcAABB();
    auto AABB = structure.AABB;

    // Corners
    cVector c1 = {AABB[0], AABB[1], AABB[2]};
    cVector c2 = {AABB[3], AABB[1], AABB[2]};
    cVector c3 = {AABB[0], AABB[4], AABB[2]};
    cVector c4 = {AABB[3], AABB[4], AABB[2]};

    cVector c5 = {AABB[0], AABB[1], AABB[5]};
    cVector c6 = {AABB[3], AABB[1], AABB[5]};
    cVector c7 = {AABB[0], AABB[4], AABB[5]};
    cVector c8 = {AABB[3], AABB[4], AABB[5]};
    {
      // Apply state
      c1 *= cMatrix::TranslationOnly(structure.State);
      c2 *= cMatrix::TranslationOnly(structure.State);
      c3 *= cMatrix::TranslationOnly(structure.State);
      c4 *= cMatrix::TranslationOnly(structure.State);
      c5 *= cMatrix::TranslationOnly(structure.State);
      c6 *= cMatrix::TranslationOnly(structure.State);
      c7 *= cMatrix::TranslationOnly(structure.State);
      c8 *= cMatrix::TranslationOnly(structure.State);

      // Calc on screen pos
      cMatrix appliedState = State;

      // seems to work for cam1, atleast
      appliedState = cMatrix::RotationInverse(appliedState);
      appliedState *= cMatrix::GetRotationMatrix({0, 1, 0}, 180);
      appliedState *= cMatrix::GetRotationMatrix({0, 0, 1}, 180);

      cMatrix pm = cMatrix::GetProjectionMatrix(1, 2000, 60) * appliedState;
      c1 *= pm;
      c2 *= pm;
      c3 *= pm;
      c4 *= pm;
      c5 *= pm;
      c6 *= pm;
      c7 *= pm;
      c8 *= pm;

      if (c1.W < 0 || c2.W < 0 || c3.W < 0 || c4.W < 0 || c5.W < 0 ||
          c6.W < 0 || c7.W < 0 || c8.W < 0) {
        continue;
      }

      auto& d = drawer;
      int ro = +((drawer.Width - drawer.Height) / 2);

      c1.X = (d.Height / 2) + ((c1.X / c1.W) * (d.Height / 2)) + ro;
      c1.Y = (d.Height / 2) + ((c1.Y / c1.W) * (d.Height / 2));
      c2.X = (d.Height / 2) + ((c2.X / c2.W) * (d.Height / 2)) + ro;
      c2.Y = (d.Height / 2) + ((c2.Y / c2.W) * (d.Height / 2));
      c3.X = (d.Height / 2) + ((c3.X / c3.W) * (d.Height / 2)) + ro;
      c3.Y = (d.Height / 2) + ((c3.Y / c3.W) * (d.Height / 2));
      c4.X = (d.Height / 2) + ((c4.X / c4.W) * (d.Height / 2)) + ro;
      c4.Y = (d.Height / 2) + ((c4.Y / c4.W) * (d.Height / 2));

      c5.X = (d.Height / 2) + ((c5.X / c5.W) * (d.Height / 2)) + ro;
      c5.Y = (d.Height / 2) + ((c5.Y / c5.W) * (d.Height / 2));
      c6.X = (d.Height / 2) + ((c6.X / c6.W) * (d.Height / 2)) + ro;
      c6.Y = (d.Height / 2) + ((c6.Y / c6.W) * (d.Height / 2));
      c7.X = (d.Height / 2) + ((c7.X / c7.W) * (d.Height / 2)) + ro;
      c7.Y = (d.Height / 2) + ((c7.Y / c7.W) * (d.Height / 2));
      c8.X = (d.Height / 2) + ((c8.X / c8.W) * (d.Height / 2)) + ro;
      c8.Y = (d.Height / 2) + ((c8.Y / c8.W) * (d.Height / 2));
    }

    RGB col = structure.WasCollidingLastCheck ? RGB{255, 0, 0} : RGB{0, 0, 255};

    drawer.DrawSquare(c1.X, c1.Y, c2.X, c2.Y, c3.X, c3.Y, c4.X, c4.Y, col);
    drawer.DrawSquare(c5.X, c5.Y, c6.X, c6.Y, c7.X, c7.Y, c8.X, c8.Y, col);

    drawer.DrawSquare(c1.X, c1.Y, c2.X, c2.Y, c5.X, c5.Y, c6.X, c6.Y, col);
    drawer.DrawSquare(c3.X, c3.Y, c4.X, c4.Y, c7.X, c7.Y, c8.X, c8.Y, col);
  }
}

void CameraPerspective::HandleMouseEvent(const int type, const int d1,
                                         const int d2) {}

void CameraPerspective::RegisterKeyCallbacks() {
  OnKeyCallbacks[75] = {false, [](const bool down, Camera& c) {  // PageUp
                          c.State *= cMatrix::GetTranslationMatrix(0, -3, 0);
                        }};

  OnKeyCallbacks[78] = {false, [](const bool down, Camera& c) {  // PageDown
                          c.State *= cMatrix::GetTranslationMatrix(0, 3, 0);
                        }};

  OnKeyCallbacks[82] = {false, [](const bool down, Camera& c) {  // ArrowUp
                          c.State *= cMatrix::GetTranslationMatrix(0, 0, -3);
                        }};

  OnKeyCallbacks[81] = {false, [](const bool down, Camera& c) {  // ArrowDown
                          c.State *= cMatrix::GetTranslationMatrix(0, 0, 3);
                        }};

  OnKeyCallbacks[80] = {false, [](const bool down, Camera& c) {  // ArrowLeft
                          c.State *= cMatrix::GetTranslationMatrix(-3, 0, 0);
                        }};

  OnKeyCallbacks[79] = {false, [](const bool down, Camera& c) {  // ArrowRight
                          c.State *= cMatrix::GetTranslationMatrix(3, 0, 0);
                        }};

  {
    OnKeyCallbacks[SDL_SCANCODE_Y] = {
        false, [](const bool down, Camera& c) {
          auto tmp = c.State;
          c.State = cMatrix::GetIdentityMatrix();
          c.State *= cMatrix::GetRotationMatrix({1, 0, 0}, -1);
          c.State *= tmp;
        }};

    OnKeyCallbacks[SDL_SCANCODE_H] = {
        false, [](const bool down, Camera& c) {
          auto tmp = c.State;
          c.State = cMatrix::GetIdentityMatrix();
          c.State *= cMatrix::GetRotationMatrix({1, 0, 0}, 1);
          c.State *= tmp;
        }};

    OnKeyCallbacks[SDL_SCANCODE_G] = {
        false, [](const bool down, Camera& c) {
          auto tmp = c.State;
          c.State = cMatrix::GetIdentityMatrix();
          c.State *= cMatrix::GetRotationMatrix({0, 1, 0}, 1);
          c.State *= tmp;
        }};

    OnKeyCallbacks[SDL_SCANCODE_J] = {
        false, [](const bool down, Camera& c) {
          auto tmp = c.State;
          c.State = cMatrix::GetIdentityMatrix();
          c.State *= cMatrix::GetRotationMatrix({0, 1, 0}, -1);
          c.State *= tmp;
        }};

    OnKeyCallbacks[SDL_SCANCODE_T] = {
        false, [](const bool down, Camera& c) {
          auto tmp = c.State;
          c.State = cMatrix::GetIdentityMatrix();
          c.State *= cMatrix::GetRotationMatrix({0, 0, 1}, 1);
          c.State *= tmp;
        }};

    OnKeyCallbacks[SDL_SCANCODE_U] = {
        false, [](const bool down, Camera& c) {
          auto tmp = c.State;
          c.State = cMatrix::GetIdentityMatrix();
          c.State *= cMatrix::GetRotationMatrix({0, 0, 1}, -1);
          c.State *= tmp;
        }};

    OnKeyCallbacks[SDL_SCANCODE_I] = {false, [](const bool down, Camera& c) {
                                        c.State = cMatrix::GetIdentityMatrix();
                                      }};
  }
}

void CameraPerspective::CallKeyCallbacks() {
  for (const auto& [key, onKeyCallback] : OnKeyCallbacks) {
    if (onKeyCallback.first) {
      onKeyCallback.second(onKeyCallback.first, *this);
    }
  }
}

void CameraPerspective::HandleKeyEvent(const int type, const int d1,
                                       const int d2) {
  if ((type == -3 || type == -4) &&
      OnKeyCallbacks.find(d2) != OnKeyCallbacks.end()) {
    OnKeyCallbacks[d2].first = type == -4;
  }

  // std::cout << State << "\n";
}
