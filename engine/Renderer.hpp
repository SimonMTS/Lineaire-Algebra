#pragma once
#include <map>
#include <memory>
#include <vector>

#include "Camera.hpp"
#include "Shader.hpp"
#include "Structure.hpp"
using namespace std;
using std::map;
using std::vector;

class Renderer {
  using KeyCallback =
      pair<bool, function<void(const bool down, const int key, Renderer& r)>>;

 private:
  map<int, KeyCallback> OnKeyCallbacks;

 public:
  double OriginX = 5;
  double OriginY = 5;
  double OriginZ = 5;
  unique_ptr<Shader> Drawer;

  vector<pair<cVector, unique_ptr<Camera>>> Cameras;
  int ActiveCamera = 0;

  vector<Structure> Structures;
  Structure Player;
  double Speed = 0;

  Renderer(const Structure& p);
  void Init();

  void OnResize(const int width, const int height);
  void OnKey(const int key,
             const function<void(const bool down, const int key, Renderer& r)>&
                 callback);
  void OnMouse(const function<void()>& callback);

  void AddStructure(const Structure& s);

  void AddCamera(const cVector& pos, unique_ptr<Camera> cam);
};
