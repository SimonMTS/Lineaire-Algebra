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
}

void CameraPerspective::HandleMouseEvent(const int type, const int d1,
                                         const int d2) {}

void CameraPerspective::RegisterKeyCallbacks() {
  OnKeyCallbacks[75] = {false, [](const bool down, Camera& c) {  // PageUp
                          c.State *= cMatrix::GetTranslationMatrix(0, 3, 0);
                        }};

  OnKeyCallbacks[78] = {false, [](const bool down, Camera& c) {  // PageDown
                          c.State *= cMatrix::GetTranslationMatrix(0, -3, 0);
                        }};

  OnKeyCallbacks[82] = {false, [](const bool down, Camera& c) {  // ArrowUp
                          c.State *= cMatrix::GetTranslationMatrix(0, 0, 3);
                        }};

  OnKeyCallbacks[81] = {false, [](const bool down, Camera& c) {  // ArrowDown
                          c.State *= cMatrix::GetTranslationMatrix(0, 0, -3);
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

  std::cout << State << "\n";
}
