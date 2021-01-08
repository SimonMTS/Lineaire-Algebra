#include "../engine/Camera2D.hpp"
#include "../engine/CameraPerspective.hpp"
#include "../engine/GoalBuilder.hpp"
#include "../engine/PlayerBuilder.hpp"
#include "../engine/Renderer.hpp"
using std::make_unique;

int main() {
  auto player = PlayerBuilder::GetPlayer();
  player.State *= cMatrix::GetTranslationMatrix(-100, 0, -100);
  player.RegisterPerTickAction(
      [](const int tick, Structure& structure, Renderer& r) {
        auto camPos = structure.State;
        camPos *= cMatrix::GetTranslationMatrix(0, 0, -100);

        r.Cameras[2]->State = camPos;
      });

  Renderer r{player};

  {
    auto thing = GoalBuilder::GetGoal();
    thing.State *= cMatrix::GetTranslationMatrix(100, -50, 100);
    thing.State *= cMatrix::GetRotationMatrix((cVector{1, 1, 1}).Normalized(), 45);
    thing.RegisterPerTickAction(
        [](const int tick, Structure& structure, Renderer& r) {
          const double scale = 1.0 - ((tick - 50.0) / 4000);
          //structure.State *= cMatrix::GetScalingMatrix(scale, scale, scale);

          if (tick == 100) {
            structure.State = cMatrix::GetIdentityMatrix() *
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
    thing.RegisterPerTickAction(
        [](const int tick, Structure& structure, Renderer& r) {
          const double scale = 1.0 - ((tick - 50.0) / 4000);
          //structure.State *= cMatrix::GetScalingMatrix(scale, scale, scale);

          if (tick == 100) {
            structure.State = cMatrix::GetIdentityMatrix() *
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
    thing.RegisterPerTickAction(
        [](const int tick, Structure& structure, Renderer& r) {
          const double scale = 1.0 - ((tick - 50.0) / 4000);
          //structure.State *= cMatrix::GetScalingMatrix(scale, scale, scale);

          if (tick == 100) {
            structure.State = cMatrix::GetIdentityMatrix() *
                cMatrix::GetTranslationMatrix(0, 0, 150) *
                cMatrix::GetRotationMatrix((cVector{1, 1, 1}).Normalized(), 45);
          }
        });
    r.AddStructure(thing);
  }

  {
    auto perCam = make_unique<CameraPerspective>();
    perCam->State *= cMatrix::GetRotationMatrix({1, 0, 0}, -90);
    perCam->State *= cMatrix::GetTranslationMatrix(0, -2000, 0);
    perCam->RegisterKeyCallbacks();
    r.AddCamera(move(perCam));
  }

  {
    auto cam2D = make_unique<Camera2D>();
    //cam2D->State *= cMatrix::GetRotationMatrix({0, 0, 1}, 90);
    //cam2D->State *= cMatrix::GetTranslationMatrix(-50, -50, -50);
    r.AddCamera(move(cam2D));
  }

  {
    r.AddCamera(make_unique<CameraPerspective>());
  }

  {
    auto perCam = make_unique<CameraPerspective>();
    perCam->State *= cMatrix::GetRotationMatrix({1, 0, 0}, 2);
    perCam->State *= cMatrix::GetTranslationMatrix(50, 50, -800);
    perCam->RegisterKeyCallbacks();
    r.AddCamera(move(perCam));
  }

  {  // Switch camera
    r.OnKey(58, [](const bool down, const int key, Renderer& r) {  // F1
      r.ActiveCamera = 0;
    });

    r.OnKey(59, [](const bool down, const int key, Renderer& r) {  // F2
      r.ActiveCamera = 1;
    });

    r.OnKey(60, [](const bool down, const int key, Renderer& r) {  // F3
      r.ActiveCamera = 2;
    });

    r.OnKey(61, [](const bool down, const int key, Renderer& r) {  // F4
      r.ActiveCamera = 3;
    });
  }

  const double delta = 3;
  {  // Turn right and left
    r.OnKey(4, [delta](const bool down, const int key, Renderer& r) {  // A
      r.Player.State *= cMatrix::GetRotationMatrix({0, 1, 0}, -delta);
    });

    r.OnKey(7, [delta](const bool down, const int key, Renderer& r) {  // D
      r.Player.State *= cMatrix::GetRotationMatrix({0, 1, 0}, delta);
    });
  }

  {  // Turn up and down
    r.OnKey(26, [delta](const bool down, const int key, Renderer& r) {  // W
      r.Player.State *= cMatrix::GetRotationMatrix({1, 0, 0}, -delta);
    });

    r.OnKey(22, [delta](const bool down, const int key, Renderer& r) {  // S
      r.Player.State *= cMatrix::GetRotationMatrix({1, 0, 0}, delta);
    });
  }

  {                                                                // Roll
    r.OnKey(20, [delta](const bool down, const int key, Renderer& r) {  // Q
      r.Player.State *= cMatrix::GetRotationMatrix({0, 0, 1}, delta);
    });

    r.OnKey(8, [delta](const bool down, const int key, Renderer& r) {  // E
      r.Player.State *= cMatrix::GetRotationMatrix({0, 0, 1}, -delta);
    });
  }

  {  // Move and reset
    r.OnKey(225, [](const bool down, const int key, Renderer& r) {  // Shift
      r.Speed += r.Speed > 5 ? 0 : 0.5;
    });

    r.OnKey(21, [](const bool down, const int key, Renderer& r) {  // R
      r.Player.State = cMatrix::GetIdentityMatrix();
    });
  }

  r.Init();
}
