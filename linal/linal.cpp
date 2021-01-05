#include "../engine/Camera2D.hpp"
#include "../engine/CameraPerspective.hpp"
#include "../engine/PlayerBuilder.hpp"
#include "../engine/Renderer.hpp"

int main() {
  auto player = PlayerBuilder::GetPlayer();
  // player.Pos = {0, 0, 0};
  player.State = player.State * cMatrix::GetTranslationMatrix(0, 0, 0);

  auto thing = PlayerBuilder::GetPlayer();
  // thing.Pos = {100, 0, 100};
  thing.State = thing.State * cMatrix::GetTranslationMatrix(100, 0, 100);

  Renderer r{player};
  r.AddStructure(thing);

  auto perCam = make_unique<CameraPerspective>();
  perCam->Rotation = {90, 180, 0};
  r.AddCamera({0, 1000, 0}, move(perCam));

  r.AddCamera({50, 50, 50}, make_unique<Camera2D>());

  r.OnKey(58, [](const bool down, const int key, Renderer& r) {  // F1
    r.ActiveCamera = 0;
  });

  r.OnKey(59, [](const bool down, const int key, Renderer& r) {  // F2
    r.ActiveCamera = 1;
  });

  r.OnKey(4, [](const bool down, const int key, Renderer& r) {  // A
    r.Player.State = r.Player.State * cMatrix::GetRotationMatrix({0, 1, 0}, 3);
  });

  r.OnKey(7, [](const bool down, const int key, Renderer& r) {  // D
    r.Player.State = r.Player.State * cMatrix::GetRotationMatrix({0, 1, 0}, -3);
  });

  r.OnKey(26, [](const bool down, const int key, Renderer& r) {  // W
    r.Player.State = r.Player.State * cMatrix::GetRotationMatrix({1, 0, 0}, -3);
  });

  r.OnKey(22, [](const bool down, const int key, Renderer& r) {  // S
    r.Player.State = r.Player.State * cMatrix::GetRotationMatrix({1, 0, 0}, 3);
  });

  r.OnKey(20, [](const bool down, const int key, Renderer& r) {  // Q
    r.Player.State = r.Player.State * cMatrix::GetRotationMatrix({0, 0, 1}, -3);
  });

  r.OnKey(8, [](const bool down, const int key, Renderer& r) {  // E
    r.Player.State = r.Player.State * cMatrix::GetRotationMatrix({0, 0, 1}, 3);
  });

  r.OnKey(225, [](const bool down, const int key, Renderer& r) {  // Shift
    r.Speed += r.Speed > 5 ? 0 : 0.5;
  });

  r.OnKey(21, [](const bool down, const int key, Renderer& r) {  // R
    r.Player.State = cMatrix::GetIdentityMatrix();
  });

  r.Init();
}
