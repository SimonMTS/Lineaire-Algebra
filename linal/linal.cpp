#include "../engine/Adder.hpp"

auto getMS() {
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
      .count();
}

int main() {
  std::cout << "       W : pitch down\n";
  std::cout << "       S : pitch up\n";
  std::cout << "       Q : roll left\n";
  std::cout << "       E : roll right\n";
  std::cout << "       A : turn left\n";
  std::cout << "       D : turn right\n";
  std::cout << "         : \n";
  std::cout << "   Shift : increase speed\n";
  std::cout << "   Space : shoot\n";
  std::cout << "         : \n";
  std::cout << "         : \n";
  std::cout << "   Lctrl : move backward";
  std::cout << "         : \n";
  std::cout << "       Y : pitch camera down\n";
  std::cout << "       H : pitch camera up\n";
  std::cout << "       T : roll camera left\n";
  std::cout << "       U : roll camera right\n";
  std::cout << "       G : turn camera left\n";
  std::cout << "       J : turn camera right\n";
  std::cout << "         : \n";
  std::cout << "      Up : move camera forward\n";
  std::cout << "    Down : move camera backward\n";
  std::cout << "    Left : move camera left\n";
  std::cout << "   Right : move camera right\n";
  std::cout << "  PageUp : move camera ip\n";
  std::cout << "  PageDn : move camera down\n";
  std::cout << "         : \n";
  std::cout << " F{1..4} : switch camera\n";
  std::cout << "       Z : toggle shooting helpline\n";
  std::cout << "       X : toggle orientation lines\n";
  std::cout << "       C : toggle AABB\n";
  //std::cout << "       V : toggle camera orientation lines (wrong)\n";

  Renderer r = Adder::AddPlayer();
  Adder::AddGoals(r);
  Adder::AddCameras(r);

  // Add KeyBindings
  {
    const double delta = 1;
    {                                    // Turn right and left
      r.OnKey(4, [delta](Renderer& r) {  // A
        r.Player.State *= cMatrix::GetRotationMatrix({0, 1, 0}, -delta);
      });

      r.OnKey(7, [delta](Renderer& r) {  // D
        r.Player.State *= cMatrix::GetRotationMatrix({0, 1, 0}, delta);
      });
    }

    {                                     // Turn up and down
      r.OnKey(26, [delta](Renderer& r) {  // W
        r.Player.State *= cMatrix::GetRotationMatrix({1, 0, 0}, -delta);
      });

      r.OnKey(22, [delta](Renderer& r) {  // S
        r.Player.State *= cMatrix::GetRotationMatrix({1, 0, 0}, delta);
      });
    }

    {                                     // Roll
      r.OnKey(20, [delta](Renderer& r) {  // Q
        r.Player.State *= cMatrix::GetRotationMatrix({0, 0, 1}, delta);
      });

      r.OnKey(8, [delta](Renderer& r) {  // E
        r.Player.State *= cMatrix::GetRotationMatrix({0, 0, 1}, -delta);
      });
    }

    {                                 // Move, shoot, and reset
      r.OnKey(225, [](Renderer& r) {  // Shift
        r.Speed += r.Speed > 5 ? 0 : 0.5;
      });

      r.OnKey(224, [](Renderer& r) {  // lCTRL
        r.Player.State *= cMatrix::GetTranslationMatrix(0, 0, -5);
      });

      auto lastShot = getMS();
      r.OnKey(44, [&lastShot](Renderer& r) {  // Space
        auto now = getMS();
        if (lastShot > now - 100) return;
        lastShot = now;

        Structure bullet = BulletBuilder::GetBullet();
        bullet.State *= r.Player.State;
        bullet.State *= cMatrix::GetTranslationMatrix(0, 0, 35);
        double speed = r.Speed;

        bullet.RegisterPerTickAction(
            [bullet, speed](const int tick, Structure& structure, Renderer& r) {
              structure.State *= cMatrix::GetTranslationMatrix(0, 0, 5 + speed);
              structure.Count++;

              if (structure.Count > 100) {
                r.Structures.erase(std::remove(r.Structures.begin(),
                                               r.Structures.end(), bullet),
                                   r.Structures.end());
              }
            });

        r.AddStructure(bullet);
      });

      r.OnKey(21, [](Renderer& r) {  // R
        r.Player.State = cMatrix::GetIdentityMatrix();
      });

      auto lastZ = getMS();
      r.OnKey(29, [&lastZ](Renderer& r) {  // Z
        auto now = getMS();
        if (lastZ > now - 500) return;
        lastZ = now;

        r.show_helpline = !r.show_helpline;
      });

      auto lastX = getMS();
      r.OnKey(27, [&lastX](Renderer& r) {  // X
        auto now = getMS();
        if (lastX > now - 500) return;
        lastX = now;

        r.show_orientation = !r.show_orientation;
      });

      auto lastC = getMS();
      r.OnKey(6, [&lastC](Renderer& r) {  // C
        auto now = getMS();
        if (lastC > now - 500) return;
        lastC = now;

        r.show_AABB = !r.show_AABB;
      });

      auto lastV = getMS();
      r.OnKey(25, [&lastV](Renderer& r) {  // V
        auto now = getMS();
        if (lastV > now - 500) return;
        lastV = now;

        r.show_camera_orientation = !r.show_camera_orientation;
      });
    }

    {                                // Switch camera
      r.OnKey(58, [](Renderer& r) {  // F1
        r.ActiveCamera = 0;
      });

      r.OnKey(59, [](Renderer& r) {  // F2
        r.ActiveCamera = 1;
      });

      r.OnKey(60, [](Renderer& r) {  // F3
        r.ActiveCamera = 2;
      });

      r.OnKey(61, [](Renderer& r) {  // F4
        r.ActiveCamera = 3;
      });
    }
  }

  r.Init();
}
