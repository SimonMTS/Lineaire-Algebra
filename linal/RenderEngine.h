#pragma once
#include "Camera.h"
#include "Camera2D.h"
#include "CameraPerspective.h"
#include "Renderer.h"
#include "SDL2Wrapper.h"
#include "Structure.h"
#include "Shader.h"
using std::make_unique;
using std::pair;
using std::tuple;
using std::get;
using std::unique_ptr;

class RenderEngine : public Renderer {
 public:
  double OriginX = 5;
  double OriginY = 5;
  double OriginZ = 5;
  unique_ptr<Shader> Sdl;

  vector<pair<Point3D, Structure>> Structures;
  vector<pair<Point3D, unique_ptr<Camera>>> Cameras;

  int ActiveCamera = 0;
  int FrameLoop200 = 0;

  void BeforeEach();
  void OnKey(int event, int key);
  void OnMouse(int event, int x, int y);
  void OnResize(int width, int height);

  void DrawGrid();

 public:
  RenderEngine();
  void Init();

  void AddLine(Line3D& l) override;
  void AddStructure(pair<Point3D, Structure>& s);

  void AddCamera(Point3D pos, unique_ptr<Camera> cam);
};
