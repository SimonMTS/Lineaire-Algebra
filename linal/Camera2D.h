#pragma once
#include "Camera.h"

class Camera2D : public Camera {
 private:
  tuple<bool, int, int> IsDragging = {false, 0, 0};

 public:
  void DrawGrid(SDL2Wrapper& Sdl, Point3D& pos) override;
  void DrawStructures(SDL2Wrapper& Sdl,
                      vector<pair<Point3D, Structure>>& Structures,
                      Point3D& pos) override;

  void MousePassthrough(int event, int x, int y, std::string& rendEng) override;
};
