#include "../engine/Camera2D.hpp"
#include "../engine/CameraPerspective.hpp"
#include "../engine/PlayerBuilder.hpp"
#include "../engine/Renderer.hpp"

int main() {
  auto player = PlayerBuilder::GetPlayer();

  auto thing = PlayerBuilder::GetPlayer();
  thing.Pos = {100, 100, 100};

  Renderer r{player};
  r.AddStructure(thing);
  //r.Player *= cMatrix::GetTranslationMatrix(0, 0, 0);
  //r.Player.State = r.Player.State * cMatrix::GetTranslationMatrix(0, 0, 0);

  auto perCam = make_unique<CameraPerspective>();
  perCam->Rotation = {90, 180, 0};
  r.AddCamera({100, -1000, 100}, move(perCam));

  r.AddCamera({50, 50, 50}, make_unique<Camera2D>());

  // F1
  r.OnKey(58, [](const bool down, const int key, Renderer& r) {
    r.ActiveCamera = 0;
  });

  // F2
  r.OnKey(59, [](const bool down, const int key, Renderer& r) {
    r.ActiveCamera = 1;
  });


  // A
  r.OnKey(4, [](const bool down, const int key, Renderer& r) {
    cVector at90deg = {0, 1, 0};
    r.Player.Dir = r.Player.Dir * cMatrix::GetRotationMatrix(at90deg, 3);
  });
  // D
  r.OnKey(7, [](const bool down, const int key, Renderer& r) {
    cVector at90deg = {0, 1, 0};
    r.Player.Dir = r.Player.Dir * cMatrix::GetRotationMatrix(at90deg, -3);
  });

  // W
  r.OnKey(26, [](const bool down, const int key, Renderer& r) {
    r.Player.Dir = r.Player.Dir * cMatrix::GetRotationMatrix(cVector{1, 0, 0}, -3);
  });
  // S
  r.OnKey(22, [](const bool down, const int key, Renderer& r) {
    r.Player.Dir = r.Player.Dir * cMatrix::GetRotationMatrix(cVector{1, 0, 0}, 3);
  });

  // Q
  r.OnKey(20, [](const bool down, const int key, Renderer& r) {
    r.Player.Rot -= 3;
    r.Player.Rot += r.Player.Rot < 0 ? 360 : 0;
  });
  // E
  r.OnKey(8, [](const bool down, const int key, Renderer& r) {
    r.Player.Rot += 3;
    r.Player.Rot -= r.Player.Rot > 360 ? 360 : 0;
  });


  // Shift
  r.OnKey(225, [](const bool down, const int key, Renderer& r) {
    r.Speed += r.Speed > 5 ? 0 : 0.5;
  });

  // R
  r.OnKey(21, [](const bool down, const int key, Renderer& r) {
    std::cout << "\nReset\n";

    r.Player.Rot = 0;
    r.Player.Dir = {0, 0, 1};

  });

  r.Init();
}
