#pragma once
#include <map>
#include <memory>
#include <vector>

#include "Camera.hpp"
#include "Shader.hpp"
#include "Structure.hpp"
using std::map;
using std::vector;

class Renderer {
  using KeyCallback =
      pair<bool, function<void(const bool down, const int key, Renderer& r)>>;

 private:
  map<int, KeyCallback> OnKeyCallbacks;

 public:
  unique_ptr<Shader> Drawer;

  vector<unique_ptr<Camera>> Cameras;
  int ActiveCamera = 0;

  vector<Structure> Structures;
  Structure Player;
  double Speed = 0;

  Renderer(const Structure& p);
  void Init();

  void OnKey(const int key,
             const function<void(const bool down, const int key, Renderer& r)>&
                 callback);

  void AddStructure(const Structure& s);

  void AddCamera(unique_ptr<Camera> cam);
};
