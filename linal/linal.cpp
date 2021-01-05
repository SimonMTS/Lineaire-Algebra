#include "../engine/Camera2D.hpp"
#include "../engine/CameraPerspective.hpp"
#include "../engine/PlayerBuilder.hpp"
#include "../engine/Renderer.hpp"

int main() {
  auto player = PlayerBuilder::GetPlayer();
  player.Pos = {0, 0, 0};

  auto thing = PlayerBuilder::GetPlayer();
  thing.Pos = {100, 0, 100};

  Renderer r{player};
  r.AddStructure(thing);

  auto perCam = make_unique<CameraPerspective>();
  perCam->Rotation = {90, 180, 0};
  r.AddCamera({0, 1000, 0}, move(perCam));

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
    r.Player *= cMatrix::GetRotationMatrix(at90deg, 3);
  });
  // D
  r.OnKey(7, [](const bool down, const int key, Renderer& r) {
    cVector at90deg = {0, 1, 0};
    r.Player.Dir = r.Player.Dir * cMatrix::GetRotationMatrix(at90deg, -3);
    r.Player *= cMatrix::GetRotationMatrix(at90deg, -3);
  });

  // W
  r.OnKey(26, [](const bool down, const int key, Renderer& r) {
    cVector at90deg = {1, 0, 0};
    r.Player.Dir = r.Player.Dir * cMatrix::GetRotationMatrix(at90deg, -3);
    r.Player *= cMatrix::GetRotationMatrix(at90deg, -3);
  });
  // S
  r.OnKey(22, [](const bool down, const int key, Renderer& r) {
    cVector at90deg = {1, 0, 0};
    r.Player.Dir = r.Player.Dir * cMatrix::GetRotationMatrix(at90deg, 3);
    r.Player *= cMatrix::GetRotationMatrix(at90deg, 3);
  });

  // Q
  r.OnKey(20, [](const bool down, const int key, Renderer& r) {
    r.Player.Rot -= 3;
    r.Player.Rot += r.Player.Rot < 0 ? 360 : 0;
    r.Player *= cMatrix::GetRotationMatrix(r.Player.Dir, -3);
  });
  // E
  r.OnKey(8, [](const bool down, const int key, Renderer& r) {
    r.Player.Rot += 3;
    r.Player.Rot -= r.Player.Rot > 360 ? 360 : 0;
    r.Player *= cMatrix::GetRotationMatrix(r.Player.Dir, 3);
  });


  // Shift
  r.OnKey(225, [](const bool down, const int key, Renderer& r) {
    r.Speed += r.Speed > 5 ? 0 : 0.5;
  });

  // R
  r.OnKey(21, [](const bool down, const int key, Renderer& r) {

    r.Player *= cMatrix::GetRotationMatrix(r.Player.Dir, -r.Player.Rot);
    r.Player.Rot = 0;

    {
      cVector from = r.Player.Dir;
      cVector to = {0, 0, 1};
      cVector distance = from - to;

      if (distance.Length() > 0.001) {
        cVector directionA = from;
        cVector directionB = to;

        double rotationAngle =
            acos(directionA.DotProduct(directionB)) * (180.0 / M_PI);
        cVector rotationAxis = directionA.CrossProduct(directionB).Normalized();

        if (abs(rotationAngle) > 0.001) {
          auto rm = cMatrix::GetRotationMatrix(rotationAxis, -rotationAngle);
          r.Player *= rm;
        }
      }
    }
    r.Player.Dir = {0, 0, 1};

  });

  r.Init();
}
