#include "CameraPerspective.hpp"

void CameraPerspective::DrawStructures(SDL2Wrapper& drawer,
                                       vector<Structure>& structures) {
  for (auto& structure : structures) {
    for (auto& component : structure.Components) {
      for (auto sqr : component.Squares) {
        // Calc position in structure
        sqr.P1 = sqr.P1 + component.Pos;
        sqr.P2 = sqr.P2 + component.Pos;
        sqr.P3 = sqr.P3 + component.Pos;
        sqr.P4 = sqr.P4 + component.Pos;

        // Apply state
        sqr.P1 = sqr.P1 * structure.State;
        sqr.P2 = sqr.P2 * structure.State;
        sqr.P3 = sqr.P3 * structure.State;
        sqr.P4 = sqr.P4 * structure.State;

        // Calc on screen pos
        cMatrix pm = cMatrix::GetProjectionMatrix(1, 2000, 60) * State;
        sqr.P1 = sqr.P1 * pm;
        sqr.P2 = sqr.P2 * pm;
        sqr.P3 = sqr.P3 * pm;
        sqr.P4 = sqr.P4 * pm;

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

void CameraPerspective::HandleMouseEvent(const int type, const int d1,
                                         const int d2) {
  // std::cout << "111111\n";
}

void CameraPerspective::RegisterKeyCallbacks() {
  OnKeyCallbacks[75] = {false, [](const bool down, Camera& c) {  // PageUp
                          c.State =
                              c.State * cMatrix::GetTranslationMatrix(0, 3, 0);
                        }};

  OnKeyCallbacks[78] = {false, [](const bool down, Camera& c) {  // PageDown
                          c.State =
                              c.State * cMatrix::GetTranslationMatrix(0, -3, 0);
                        }};

  OnKeyCallbacks[82] = {false, [](const bool down, Camera& c) {  // ArrowUp
                          c.State =
                              c.State * cMatrix::GetTranslationMatrix(0, 0, -3);
                        }};

  OnKeyCallbacks[81] = {false, [](const bool down, Camera& c) {  // ArrowDown
                          c.State =
                              c.State * cMatrix::GetTranslationMatrix(0, 0, 3);
                        }};

  OnKeyCallbacks[80] = {false, [](const bool down, Camera& c) {  // ArrowLeft
                          c.State =
                              c.State * cMatrix::GetTranslationMatrix(3, 0, 0);
                        }};

  OnKeyCallbacks[79] = {false, [](const bool down, Camera& c) {  // ArrowRight
                          c.State =
                              c.State * cMatrix::GetTranslationMatrix(-3, 0, 0);
                        }};
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
}
