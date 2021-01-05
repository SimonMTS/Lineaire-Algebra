#pragma once
#include "Camera.hpp"
using std::tuple;
using std::get;

class Camera2D : public Camera {
 private:
  tuple<bool, int, int> IsDragging = {false, 0, 0};

 public:
  void DrawGrid(SDL2Wrapper& drawer, const cVector& pos) override;
  void DrawStructures(SDL2Wrapper& drawer, vector<Structure>& structures,
                      const cVector& pos) override;
  cVector HandleMouseEvent(const int type, const int d1, const int d2) override;
};
