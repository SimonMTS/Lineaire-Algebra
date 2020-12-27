#pragma once
#include "Line3D.h"
#include "Renderer.h"
#include "SDL2Wrapper.h"
using std::pair;

class rendererPerspective : public Renderer {
 private:
  double OriginX = 5;
  double OriginY = 5;
  double OriginZ = 5;
  unique_ptr<SDL2Wrapper> Sdl;

  vector<Line3D> Lines;

  vector<pair<Point3D, int>> Cameras;
  pair<Point3D, int> ActiveCamera = pair<Point3D, int>{{0, 0, 0}, -1};

  void BeforeEach();
  void OnKey(int event, int key);
  void OnMouse(int event);
  void OnResize(int width, int height);

  void DrawGrid();
  void DrawLines();

  void Scale(const double x, const double y, const double z);
  void Move(const double x, const double y, const double z);
  void Rotate(const int dir);

 public:
  rendererPerspective();
  void Init();

  void AddLine(Line3D& l) override;

  void AddCamera(Point3D pos, int type);
};
