#pragma once
#include <limits>

#include "Camera.hpp"
using std::get;
using std::numeric_limits;
using std::tuple;

class Camera2D : public Camera {
 private:
  tuple<bool, int, int> IsDragging = {false, 0, 0};

 public:
  void DrawGrid(SDL2Wrapper& drawer) override;
  void DrawStructures(SDL2Wrapper& drawer, vector<Structure>& structures,
                      vector<unique_ptr<Camera>>& cameras) override;
  void HandleMouseEvent(const int type, const int d1, const int d2) override;
};
