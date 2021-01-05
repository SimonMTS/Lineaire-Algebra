#pragma once
#include "SDL2Wrapper.hpp"
#include "../math/cVector.hpp"
#include "Structure.hpp"

class Camera {
 public:
  virtual void DrawGrid(SDL2Wrapper& drawer, const cVector& pos) = 0;
  virtual void DrawStructures(SDL2Wrapper& drawer,
                              vector<Structure>& structures,
                              const cVector& pos) = 0;
  virtual cVector HandleMouseEvent(const int type, const int d1, const int d2) {
    return {0, 0, 0};
  };
};
