#pragma once
#include "Camera.h"

class CameraPerspective : public Camera {
 public:
  tuple<double, double, double> Rotation = {0, 0, 0};

  void DrawGrid(SDL2Wrapper& Sdl, Point3D& pos) override;
  void DrawStructures(SDL2Wrapper& Sdl,
                      vector<pair<Point3D, Structure>>& Structures,
                      Point3D& pos) override;

  void KeyPassthrough(int event, int key, std::string& rendEng) override;
  void MousePassthrough(int event, int x, int y, std::string& rendEng) override;
};
