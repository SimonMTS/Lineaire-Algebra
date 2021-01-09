#pragma once
#include <algorithm>
#include <chrono>s

#include "../engine/BulletBuilder.hpp"
#include "../engine/Camera2D.hpp"
#include "../engine/CameraPerspective.hpp"
#include "../engine/GoalBuilder.hpp"
#include "../engine/PlayerBuilder.hpp"
#include "../engine/Renderer.hpp"
using std::make_unique;
using namespace std::chrono;

class Adder {
 public:
  static Renderer AddPlayer();

  static void AddGoals(Renderer& r);

  static void AddCameras(Renderer& r);
};
