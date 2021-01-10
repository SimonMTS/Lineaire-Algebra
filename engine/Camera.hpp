#pragma once
#include <map>

#include "../math/cVector.hpp"
#include "SDL2Wrapper.hpp"
#include "Structure.hpp"
using std::map;
using std::pair;

class Camera {
  using KeyCallback = pair<bool, function<void(const bool down, Camera& r)>>;

 protected:
  map<int, KeyCallback> OnKeyCallbacks;

 public:
  cMatrix State = cMatrix::GetIdentityMatrix();

  virtual void DrawGrid(SDL2Wrapper& drawer, bool dark_mode) = 0;
  virtual void DrawStructures(SDL2Wrapper& drawer,
                              vector<Structure>& structures,
                              vector<unique_ptr<Camera>>& cameras,
                              bool dark_mode) = 0;

  virtual void HandleMouseEvent(const int type, const int d1, const int d2){};

  virtual void RegisterKeyCallbacks(){};
  virtual void CallKeyCallbacks(){};
  virtual void HandleKeyEvent(const int type, const int d1, const int d2){};
};
