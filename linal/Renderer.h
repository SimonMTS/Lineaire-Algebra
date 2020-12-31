#pragma once
#include "Line3D.h"
using std::pair;

class Renderer {
 public:
  virtual void BeforeEach() = 0;
  virtual void OnKey(int event, int key) = 0;
  virtual void OnMouse(int event, int x, int y) = 0;
  virtual void OnResize(int width, int height) = 0;

  virtual void AddLine(Line3D& l) = 0;
};
