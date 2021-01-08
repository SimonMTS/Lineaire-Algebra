#pragma once
#include <tuple>

#include "Camera.hpp"
using std::get;
using std::tuple;

class CameraPerspective : public Camera {
 public:
  void DrawGrid(SDL2Wrapper& drawer) override{};
  void DrawStructures(SDL2Wrapper& drawer, vector<Structure>& structures,
                      vector<unique_ptr<Camera>>& cameras) override;

  void HandleMouseEvent(const int type, const int d1, const int d2) override;

  virtual void RegisterKeyCallbacks();
  void CallKeyCallbacks() override;
  void HandleKeyEvent(const int type, const int d1, const int d2) override;
};
