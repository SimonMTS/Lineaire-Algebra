#pragma once
#include "SDL2Wrapper.h"
#include "Point3D.h"
#include "Structure.h"
using std::pair;

class Camera {
 public:
  virtual void DrawGrid(SDL2Wrapper& Sdl, Point3D& pos) = 0;
  virtual void DrawStructures(SDL2Wrapper& Sdl,
                              vector<pair<Point3D, Structure>>& Structures,
                              Point3D& pos) = 0;
};
