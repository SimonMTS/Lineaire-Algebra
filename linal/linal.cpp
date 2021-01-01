#include "../engine/Camera2D.hpp"
#include "../engine/CameraPerspective.hpp"
#include "../engine/PlayerBuilder.hpp"
#include "../engine/Renderer.hpp"

int main() {
  auto player = PlayerBuilder::GetPlayer();

  Renderer r{player};
  //r.Player *= cMatrix::GetTranslationMatrix(0, 0, 0);
  //r.Player.State = r.Player.State * cMatrix::GetTranslationMatrix(0, 0, 0);

  r.AddCamera({50, 50, 50}, make_unique<Camera2D>());

  auto perCam = make_unique<CameraPerspective>();
  perCam->Rotation = {90, 180, 0};
  r.AddCamera({0, -1000, 0}, move(perCam));

  r.OnKey([](const bool down, const int key, Renderer& r) {
    // std::cout << down << " " << key << "\n";
    if (!down && key == 58) {  // F1
      r.ActiveCamera = 0;
    }

    if (!down && key == 59) {  // F2
      r.ActiveCamera = 1;
    }
  });

  r.OnKey([](const bool down, const int key, Renderer& r) {
    if (key == 7) { r.Key_D = down; }
    if (key == 7) {  // D
      //auto rm = cMatrix::GetRotationMatrix(2, 1);

      //auto fromOrigin = cMatrix::TranslationOnly(r.Player.State);
      //r.Player *= fromOrigin * rm * cMatrix::TranslationInverse(fromOrigin);
      //r.Player.State = r.Player.State * rm;
      //r.Player.tmp = r.Player.tmp * rm;

      //r.Player.Dir = r.Player.Dir * cMatrix::GetRotationMatrix(2, 1);
      //std::cout << r.Player.Dir << "\n";
    }
    if (key == 4) { r.Key_A = down; }
    if (key == 4) {  // A
      //auto rm = cMatrix::GetRotationMatrix(2, -1);

      //auto fromOrigin = cMatrix::TranslationOnly(r.Player.State);
      //r.Player *= fromOrigin * rm * cMatrix::TranslationInverse(fromOrigin);
      //r.Player.State = r.Player.State * rm;
      //r.Player.tmp = r.Player.tmp * rm;

      //r.Player.Dir = r.Player.Dir * cMatrix::GetRotationMatrix(2, -1);
    }
    
    if (key == 26) { r.Key_W = down; }
    if (key == 26) {  // W
      //auto rm = cMatrix::GetRotationMatrix(1, 1);

      //auto fromOrigin = cMatrix::TranslationOnly(r.Player.State);
      //r.Player *= fromOrigin * rm * cMatrix::TranslationInverse(fromOrigin);
      //r.Player.State = r.Player.State * rm;
      //r.Player.tmp = r.Player.tmp * rm;

      //r.Player.Dir = r.Player.Dir * cMatrix::GetRotationMatrix(1, 1);
    }
    if (key == 22) { r.Key_S = down; }
    if (key == 22) {  // S
      //auto rm = cMatrix::GetRotationMatrix(1, -1);

      //auto fromOrigin = cMatrix::TranslationOnly(r.Player.State);
      //r.Player *= fromOrigin * rm * cMatrix::TranslationInverse(fromOrigin);
      //r.Player.State = r.Player.State * rm;
      //r.Player.tmp = r.Player.tmp * rm;

      //r.Player.Dir = r.Player.Dir * cMatrix::GetRotationMatrix(1, -1);
    }
    if (key == 20) { r.Key_Q = down; }
    if (key == 20) {  // Q
      //auto rm = cMatrix::GetRotationMatrix(3, 1);

      //auto fromOrigin = cMatrix::TranslationOnly(r.Player.State);
      //r.Player *= fromOrigin * rm * cMatrix::TranslationInverse(fromOrigin);
      //r.Player.State = r.Player.State * rm;
      //r.Player.tmp = r.Player.tmp * rm;
    }
    if (key == 8) { r.Key_E = down; }
    if (key == 8) {  // E
      //auto rm = cMatrix::GetRotationMatrix(3, -1);

      //auto fromOrigin = cMatrix::TranslationOnly(r.Player.State);
      //r.Player *= fromOrigin * rm * cMatrix::TranslationInverse(fromOrigin);
      //r.Player.State = r.Player.State * rm;
      //r.Player.tmp = r.Player.tmp * rm;
    }

    if (key == 225) { r.Key_Shift = down; }
    if (down && key == 225) {  // Shift
      { // move forward
        //r.Player.Pos = r.Player.Pos + r.Player.Dir;
        //std::cout << r.Player.Pos << "\n";
        /*r.Speed = 5;*/
      }

      // auto tm = cMatrix::GetTranslationMatrix(0, 0, 10);

      // auto fromOrigin = r.Player.State;

      // std::cout << cMatrix::RotationInverse(fromOrigin) << "\n";

      {
          // move to 0,0,0
          // auto inv = cMatrix::TranslationOnly(fromOrigin);
          // inv = cMatrix::TranslationInverse(inv);
          // r.Player *= inv;
          // r.Player.State = inv * r.Player.State;
      }

      {
          // rotate straight (works on single dir)
          // auto inv = cMatrix::RotationOnly(fromOrigin);
          // inv = cMatrix::RotationInverse(inv);
          // r.Player *= inv;
          // r.Player.State = inv * r.Player.State;
      }

      {  // rotate attempt with tmp
        //std::cout << r.Player.tmp << "\n";

        {
          //cVector& tmp = r.Player.tmp;

          //double y_angle_to_rotate =
          //    (tmp.X != 0 ? (atan(tmp.Z / tmp.X) * (180.0 / M_PI)) : 0);
          //std::cout << y_angle_to_rotate << "\n";
          //r.Player *= cMatrix::GetRotationMatrix(2, y_angle_to_rotate);
          //tmp = tmp * cMatrix::GetRotationMatrix(2, y_angle_to_rotate);

          //
          //double z_angle_to_rotate =
          //    (tmp.Y != 0 ? (atan(tmp.X / tmp.Y) * (180.0 / M_PI)) : 0);
          //std::cout << z_angle_to_rotate << "\n";
          //r.Player *= cMatrix::GetRotationMatrix(3, z_angle_to_rotate);
          //tmp = tmp * cMatrix::GetRotationMatrix(3, z_angle_to_rotate);

          //
          //double x_angle_to_rotate =
          //    (tmp.Z != 0 ? (atan(tmp.Y / tmp.Z) * (180.0 / M_PI)) : 0);
          //std::cout << x_angle_to_rotate << "\n\n";
          //r.Player *= cMatrix::GetRotationMatrix(1, 1);
          //tmp = tmp * cMatrix::GetRotationMatrix(1, x_angle_to_rotate);

          
          //r.Player *= cMatrix::GetRotationMatrix(2, 1);

          // back
          //r.Player *= cMatrix::GetRotationMatrix(1, -x_angle_to_rotate);
          //tmp = tmp * cMatrix::GetRotationMatrix(1, -x_angle_to_rotate);
          //r.Player *= cMatrix::GetRotationMatrix(3, -z_angle_to_rotate);
          //tmp = tmp * cMatrix::GetRotationMatrix(3, -z_angle_to_rotate);
          //r.Player *= cMatrix::GetRotationMatrix(2, -y_angle_to_rotate);
          //tmp = tmp * cMatrix::GetRotationMatrix(2, -y_angle_to_rotate);

          //auto inv = cMatrix::RotationOnly(r.Player.State);
          //inv = cMatrix::RotationInverse(inv);
          //r.Player *= inv;
          //std::cout << r.Player.tmp << "\n";
        }

        // double y_angle_to_rotate = 0;
        // double z_angle_to_rotate = 0;
        // double x_angle_to_rotate = 0;

        {  // calc angles
           // cVector tmp = {10, 8, 6};
           // std::cout << tmp << "\n";

          // y_angle_to_rotate = atan(tmp.Z / tmp.X) * (180.0 / M_PI);
          // tmp = tmp * cMatrix::GetRotationMatrix(2, y_angle_to_rotate);
          // std::cout << tmp << "\n";

          // z_angle_to_rotate = atan(tmp.X / tmp.Y) * (180.0 / M_PI);
          // tmp = tmp * cMatrix::GetRotationMatrix(3, z_angle_to_rotate);

          // std::cout << tmp << "\n\n";
        }

        // std::cout << r.Player.tmp << "\n";
        // std::cout << y_angle_to_rotate << "\n";
        // std::cout << x_angle_to_rotate << "\n";
        // std::cout << z_angle_to_rotate << "\n";
      }

      // auto tm_fromOrigin = cMatrix::TranslationOnly(fromOrigin);
      // r.Player *= cMatrix::TranslationInverse(tm_fromOrigin);
      // auto rm_fromOrigin = cMatrix::RotationOnly(fromOrigin);
      // r.Player *= cMatrix::RotationInverse(rm_fromOrigin);
      // r.Player *= tm;
      // r.Player *= cMatrix::RotationOnly(fromOrigin);
      // r.Player *= tm_fromOrigin;

      // r.Player *= fromOrigin * tm * cMatrix::RotationInverse(fromOrigin);

      // r.Player.State *= tm;

      // r.Player.State *= cMatrix::TranslationInverse(fromOrigin);
      // r.Player.State *= cMatrix::RotationInverse(fromOrigin);

      // std::cout << fromOrigin << "\n";
    }
  });

  r.Init();
}
