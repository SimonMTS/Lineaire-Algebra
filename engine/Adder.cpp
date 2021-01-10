#include "Adder.hpp"

Renderer Adder::AddPlayer() {
  auto player = PlayerBuilder::GetPlayer();
  player.State *= cMatrix::GetTranslationMatrix(0, 0, 0);
  player.RegisterPerTickAction(
      [](const int tick, Structure& structure, Renderer& r) {
        auto playerRot = cMatrix::RotationOnly(structure.State);
        r.Cameras[2]->State = cMatrix::GetIdentityMatrix();
        r.Cameras[2]->State *= cMatrix::GetTranslationMatrix(0, 0, -100);
        playerRot = cMatrix::RotationInverse(playerRot);
        r.Cameras[2]->State *= cMatrix::GetRotationMatrix({0, 1, 0}, 180);
        r.Cameras[2]->State *= cMatrix::GetRotationMatrix({0, 0, 1}, 180);
        r.Cameras[2]->State *= playerRot;

        auto playerPos = cMatrix::TranslationOnly(structure.State);
        playerPos = cMatrix::TranslationInverse(playerPos);
        r.Cameras[2]->State *= playerPos;
      });

  Renderer r{player};

  return r;
}

void Adder::AddGoals(Renderer& r) {
  {
    auto thing = GoalBuilder::GetGoal();
    thing.State *= cMatrix::GetTranslationMatrix(100, -50, 100);
    thing.State *=
        cMatrix::GetRotationMatrix((cVector{1, 1, 1}).Normalized(), 45);
    thing.RegisterPerTickAction([](const int tick, Structure& structure,
                                   Renderer& r) {
      const double scale = 1.0 - ((tick - 50.0) / 4000);
      structure.State *= cMatrix::GetScalingMatrix(scale, scale, scale);

      structure.Components.at(1) *= cMatrix::GetRotationMatrix({0, 1, 0}, 3);
      structure.Components.at(2) *= cMatrix::GetRotationMatrix({0, 1, 0}, 3);

      if (tick == 100) {
        structure.State =
            cMatrix::GetIdentityMatrix() *
            cMatrix::GetTranslationMatrix(100, -50, 100) *
            cMatrix::GetRotationMatrix((cVector{1, 1, 1}).Normalized(), 45);
      }
    });
    r.AddStructure(thing);
  }

  {
    auto thing = GoalBuilder::GetGoal();
    thing.State *= cMatrix::GetTranslationMatrix(-100, -50, 100);
    thing.State *=
        cMatrix::GetRotationMatrix((cVector{1, 1, 1}).Normalized(), 45);
    thing.RegisterPerTickAction([](const int tick, Structure& structure,
                                   Renderer& r) {
      const double scale = 1.0 - ((tick - 50.0) / 4000);
      structure.State *= cMatrix::GetScalingMatrix(scale, scale, scale);

      structure.Components.at(1) *= cMatrix::GetRotationMatrix({0, 1, 0}, 3);
      structure.Components.at(2) *= cMatrix::GetRotationMatrix({0, 1, 0}, 3);

      if (tick == 100) {
        structure.State =
            cMatrix::GetIdentityMatrix() *
            cMatrix::GetTranslationMatrix(-100, -50, 100) *
            cMatrix::GetRotationMatrix((cVector{1, 1, 1}).Normalized(), 45);
      }
    });
    r.AddStructure(thing);
  }

  {
    auto thing = GoalBuilder::GetGoal();
    thing.State *= cMatrix::GetTranslationMatrix(0, 0, 150);
    thing.State *=
        cMatrix::GetRotationMatrix((cVector{1, 1, 1}).Normalized(), 45);
    thing.RegisterPerTickAction([](const int tick, Structure& structure,
                                   Renderer& r) {
      const double scale = 1.0 - ((tick - 50.0) / 4000);
      structure.State *= cMatrix::GetScalingMatrix(scale, scale, scale);

      structure.Components.at(1) *= cMatrix::GetRotationMatrix({0, 1, 0}, 3);
      structure.Components.at(2) *= cMatrix::GetRotationMatrix({0, 1, 0}, 3);

      if (tick == 100) {
        structure.State =
            cMatrix::GetIdentityMatrix() *
            cMatrix::GetTranslationMatrix(0, 0, 150) *
            cMatrix::GetRotationMatrix((cVector{1, 1, 1}).Normalized(), 45);
      }
    });
    r.AddStructure(thing);
  }

  {
    auto thing = GoalBuilder::GetGoal();
    thing.State *= cMatrix::GetTranslationMatrix(100, 100, -450);
    thing.State *=
        cMatrix::GetRotationMatrix((cVector{1, 1, 1}).Normalized(), 45);
    thing.RegisterPerTickAction([](const int tick, Structure& structure,
                                   Renderer& r) {
      const double scale = 1.0 - ((tick - 50.0) / 4000);
      structure.State *= cMatrix::GetScalingMatrix(scale, scale, scale);

      structure.Components.at(1) *= cMatrix::GetRotationMatrix({0, 1, 0}, 3);
      structure.Components.at(2) *= cMatrix::GetRotationMatrix({0, 1, 0}, 3);

      if (tick == 100) {
        structure.State =
            cMatrix::GetIdentityMatrix() *
            cMatrix::GetTranslationMatrix(100, 100, -450) *
            cMatrix::GetRotationMatrix((cVector{1, 1, 1}).Normalized(), 45);
      }
    });
    // r.AddStructure(thing);
  }
}

void Adder::AddCameras(Renderer& r) {
  {
    auto perCam = make_unique<CameraPerspective>();
    perCam->State *= cMatrix::GetRotationMatrix({1, 0, 0}, -90);
    perCam->State *= cMatrix::GetTranslationMatrix(0, -2000, 0);
    perCam->RegisterKeyCallbacks();
    r.AddCamera(move(perCam));
  }

  {
    auto cam2D = make_unique<Camera2D>();
    cam2D->State *= cMatrix::GetTranslationMatrix(-200, 0, 200);
    r.AddCamera(move(cam2D));
  }

  { r.AddCamera(make_unique<CameraPerspective>()); }

  {
    auto perCam = make_unique<CameraPerspective>();
    perCam->State *= cMatrix::GetRotationMatrix({1, 0, 0}, 2);
    perCam->State *= cMatrix::GetTranslationMatrix(50, 50, -800);
    perCam->RegisterKeyCallbacks();
    r.AddCamera(move(perCam));
  }
}
