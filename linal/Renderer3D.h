#pragma once
#include <vector>

#include "Line3D.h"
#include "Point3D.h"
#include "Renderer.h"
#include "SDL2Wrapper.h"
using std::vector;

enum Perspective3D { Topview, Frontview, Sideview };

class Renderer3D : public Renderer {
 private:
  Perspective3D Perspective = Perspective3D::Frontview;

  const double GridStep = 20;
  double OriginX = 20;
  double OriginY = 20;
  double OriginZ = 20;

  unique_ptr<SDL2Wrapper> Sdl;
  vector<Line3D> Lines;

  void BeforeEach();
  void OnKey(int event, int key);
  void OnMouse(int event, int x, int y);
  void OnResize(int width, int height);

  void DrawGrid();
  void DrawLines();

  void Scale(const double x, const double y, const double z);
  void Move(const double x, const double y, const double z);
  void Rotate(const int dir);

 public:
  Renderer3D();
  void Init();

  void AddLine(Line3D& l) override;
};
