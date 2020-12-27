#pragma once
#include "Camera.h"
#include "Camera2D.h"
#include "CameraPerspective.h"
#include "Renderer.h"
#include "SDL2Wrapper.h"
#include "Structure.h"
using std::make_unique;
using std::pair;
using std::unique_ptr;

class RenderEngine : public Renderer {
 private:
  double OriginX = 5;
  double OriginY = 5;
  double OriginZ = 5;
  unique_ptr<SDL2Wrapper> Sdl;

  vector<pair<Point3D, Structure>> Structures;
  vector<pair<Point3D, unique_ptr<Camera>>> Cameras;

  int ActiveCamera = 0;

  void BeforeEach();
  void OnKey(int event, int key);
  void OnMouse(int event);
  void OnResize(int width, int height);

  void DrawGrid();

  // void Scale(const double x, const double y, const double z);
  // void Move(const double x, const double y, const double z);
  // void Rotate(const int dir);

 public:
  RenderEngine();
  void Init();

  void AddLine(Line3D& l) override;
  void AddStructure(Structure& s);

  void AddCamera(Point3D pos, unique_ptr<Camera> cam);
};
