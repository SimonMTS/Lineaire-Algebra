#pragma once
#include <vector>
#include <functional>

#include "Component.hpp"
using std::vector;
using std::function;
class Renderer;

class Structure {
 private:
  function<void(const int tick, Structure& structure, Renderer& r)> PerTickAction;

 public:
  cMatrix State = cMatrix::GetIdentityMatrix();

  vector<Component> Components;

  void AddComponent(const Component& c);

  void RegisterPerTickAction(
      const function<void(const int tick, Structure& structure, Renderer& r)>&
          callback);
  void ExecutePerTickAction(const int tick, Renderer& r);

  void operator*=(const cMatrix& m);
};
