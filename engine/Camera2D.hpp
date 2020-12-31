#pragma once
#include "Camera.hpp"

class Camera2D : public Camera {
 public:
  void DrawGrid(SDL2Wrapper& drawer, const cVector& pos) override;
  void DrawStructures(SDL2Wrapper& drawer, vector<Structure>& structures,
                      const cVector& pos) override;
};
