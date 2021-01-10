#pragma once
#include <map>
#include <memory>
#include <vector>

#include "Adder.hpp"
#include "Camera.hpp"
#include "Structure.hpp"
using std::map;
using std::vector;

class Renderer {
  using KeyCallback = pair<bool, function<void(Renderer& r)>>;

 private:
  map<int, KeyCallback> OnKeyCallbacks;
  unsigned char Tick = 1;
  int Dead = 0;
  bool Won = false;

 public:
  static bool show_helpline;
  static bool show_orientation;
  static bool show_AABB;
  static bool show_camera_orientation;
  static bool dark_mode;

  unique_ptr<SDL2Wrapper> Drawer;

  vector<unique_ptr<Camera>> Cameras;
  int ActiveCamera = 0;

  vector<Structure> Structures;
  Structure Player;
  double Speed = 0;

  Renderer(const Structure& p);
  void Init();

  void OnKey(const int key, const function<void(Renderer& r)>& callback);

  void AddStructure(const Structure& s);

  void AddCamera(unique_ptr<Camera> cam);
};
