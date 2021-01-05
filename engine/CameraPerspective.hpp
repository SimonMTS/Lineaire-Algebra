#pragma once
#include <tuple>

#include "Camera.hpp"
using std::get;
using std::tuple;

class CameraPerspective : public Camera {
 public:
  tuple<double, double, double> Rotation = {0, 0, 0};

  void DrawGrid(SDL2Wrapper& drawer, const cVector& pos) override{};
  void DrawStructures(SDL2Wrapper& drawer, vector<Structure>& structures,
                      const cVector& pos) override;
};
