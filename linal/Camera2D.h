#pragma once
#include "Camera.h"
#include "SDL2Wrapper.h"
#include "Structure.h"

class Camera2D : public Camera {
 public:
  void DrawGrid(SDL2Wrapper& Sdl, Point3D& pos) override;
  void DrawStructures(SDL2Wrapper& Sdl,
                      vector<pair<Point3D, Structure>>& Structures,
                      Point3D& pos) override;
};
