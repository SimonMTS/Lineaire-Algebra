#pragma once
#include <functional>
#include <vector>
#include <limits>

#include "Component.hpp"
using std::function;
using std::numeric_limits;
using std::vector;
class Renderer;

class Structure {
 private:
  static int PrevIDs;

  function<void(const int tick, Structure& structure, Renderer& r)>
      PerTickAction;

  double GetMinPoint(const int axis);
  double GetMaxPoint(const int axis);

 public:
  int Count = 0;
  int ID;

  Structure() : ID(PrevIDs++){};

  cMatrix State = cMatrix::GetIdentityMatrix();
  vector<double> AABB = {0, 0, 0, 0, 0, 0};
  bool WasCollidingLastCheck = false;

  vector<Component> Components;

  void AddComponent(const Component& c);

  void RegisterPerTickAction(
      const function<void(const int tick, Structure& structure, Renderer& r)>&
          callback);
  void ExecutePerTickAction(const int tick, Renderer& r);

  void operator*=(const cMatrix& m);
  bool operator==(const Structure& other);

  void CalcAABB();
  bool IsCollidingWith(const Structure& other);
};