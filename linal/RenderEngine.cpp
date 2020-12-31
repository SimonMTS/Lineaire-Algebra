#include "RenderEngine.h"

#include "Camera.h"

RenderEngine::RenderEngine() {
  int width = 600;
  int height = width;

  SDL_Init(SDL_INIT_VIDEO);
  RGB bgColor = RGB(255, 255, 255);
  Sdl = std::make_unique<Shader>(width, height, bgColor);

  OnResize(width, height);
}

void RenderEngine::Init() { Sdl->OnEvent(*this); }

void RenderEngine::AddLine(Line3D& l) { throw "dont"; }

void RenderEngine::AddStructure(pair<Point3D, Structure>& s) {
  Structures.push_back(s);
}

void RenderEngine::AddCamera(Point3D pos, unique_ptr<Camera> cam) {
  Cameras.push_back({pos, move(cam)});
}

void RenderEngine::OnResize(int width, int height) {
  OriginX = width / 2;
  OriginY = height / 2;
  OriginZ = 0;
}

void RenderEngine::DrawGrid() { Sdl->SetBackground(); }

void RenderEngine::BeforeEach() {
  //{
  //  if (FrameLoop200 < 100) {
  //    Structures.at(0).second.Scale(1.005, 1.005, 1.005);
  //  }
  //  if (FrameLoop200 > 100) {
  //    Structures.at(0).second.Scale(0.995, 0.995, 0.995);
  //  }
  //}

  DrawGrid();
  Cameras[ActiveCamera].second->DrawGrid(*Sdl, Cameras[ActiveCamera].first);
  Cameras[ActiveCamera].second->DrawStructures(*Sdl, Structures,
                                               Cameras[ActiveCamera].first);
  Sdl->PushLines();

  FrameLoop200++;
  if (FrameLoop200 > 200) FrameLoop200 = 0;
}

void RenderEngine::OnKey(int event, int key) {
  std::cout << "key press\n";

  if (event == SDL_KEYUP && key == SDL_SCANCODE_F1) {
    ActiveCamera = 0;
    std::cout << "Set camera 1\n";
  }
  if (event == SDL_KEYUP && key == SDL_SCANCODE_F2) {
    ActiveCamera = 1;
    std::cout << "Set camera 2\n";
  }

  if (event == SDL_KEYDOWN && key == SDL_SCANCODE_RIGHT) {
    Cameras[ActiveCamera].first.X--;
    std::cout << "Move -x\n";
  }
  if (event == SDL_KEYDOWN && key == SDL_SCANCODE_LEFT) {
    Cameras[ActiveCamera].first.X++;
    std::cout << "Move +x\n";
  }

  if (event == SDL_KEYDOWN && key == SDL_SCANCODE_UP) {
    Cameras[ActiveCamera].first.Y--;
    std::cout << "Move -y\n";
  }
  if (event == SDL_KEYDOWN && key == SDL_SCANCODE_DOWN) {
    Cameras[ActiveCamera].first.Y++;
    std::cout << "Move +y\n";
  }

  if (event == SDL_KEYDOWN && key == SDL_SCANCODE_PAGEUP) {
    Cameras[ActiveCamera].first.Z--;
    std::cout << "Move -z\n";
  }
  if (event == SDL_KEYDOWN && key == SDL_SCANCODE_PAGEDOWN) {
    Cameras[ActiveCamera].first.Z++;
    std::cout << "Move +z\n";
  }

  if (event == SDL_KEYDOWN && key == SDL_SCANCODE_R) {
    Structures.at(0).second.Rotate(1, 1);
    Structures.at(0).second.Rotate(2, 1);
    Structures.at(0).second.Rotate(3, 1);
  }

  {
    // gas gas gas
    if (event == SDL_KEYDOWN && key == SDL_SCANCODE_LSHIFT) {
      //auto rot = Structures.at(1).second.Rotation;
      //std::cout << get<0>(rot) << "deg ";
      //std::cout << get<1>(rot) << "deg ";
      //std::cout << get<2>(rot) << "deg    \n";
       //std::cout << Structures.at(1).second.Rot << "\n";

      // Structures.at(1).second.Rotate(1, -get<0>(rot));
      // Structures.at(1).second.Rotate(2, -get<1>(rot));
      // Structures.at(1).second.Rotate(3, -get<2>(rot));

      {
        auto& asd = Structures.at(0).second;

        for (auto& object : asd.Objects) {
          Point3D localOrigin = Point3D{0, 0, 0} - object.first;

          Matrix3D tm1 = Matrix3D::GetTranslationMatrix(
              -localOrigin.X, -localOrigin.Y, -localOrigin.Z);
          Matrix3D tm2 = Matrix3D::GetTranslationMatrix(
              localOrigin.X, localOrigin.Y, localOrigin.Z);
          // Matrix3D rm = Matrix3D::GetRotationMatrix(1, 0);
          Matrix3D cm = tm1 * Matrix3D::RotationInverse(asd.Rot) * tm2;

          // asd.Rot = asd.Rot * rm;

          //Matrix3D cm1 = tm2 * Matrix3D::Inverse(asd.Rot) * tm1;
          for (auto& square : object.second.Squares) {
            square.P1 = square.P1 * cm;
            square.P2 = square.P2 * cm;
            square.P3 = square.P3 * cm;
            square.P4 = square.P4 * cm;
          }

          //Structures.at(0).second.Move(0, 0, 10);


          cm = tm1 * asd.Rot * tm2;
          for (auto& square : object.second.Squares) {
            square.P1 = square.P1 * cm;
            square.P2 = square.P2 * cm;
            square.P3 = square.P3 * cm;
            square.P4 = square.P4 * cm;
          }
        }
      }

      // Structures.at(1).second.Move(0, 0, 1);
    }

    // roll
    if (event == SDL_KEYDOWN && key == SDL_SCANCODE_Q) {
      Structures.at(0).second.Rotate(3, 1);
    }
    if (event == SDL_KEYDOWN && key == SDL_SCANCODE_E) {
      Structures.at(0).second.Rotate(3, -1);
    }

    // pitch
    if (event == SDL_KEYDOWN && key == SDL_SCANCODE_W) {
      Structures.at(0).second.Rotate(1, 1);
    }
    if (event == SDL_KEYDOWN && key == SDL_SCANCODE_S) {
      Structures.at(0).second.Rotate(1, -1);
    }

    // yaw
    if (event == SDL_KEYDOWN && key == SDL_SCANCODE_A) {
      Structures.at(0).second.Rotate(2, 1);
    }
    if (event == SDL_KEYDOWN && key == SDL_SCANCODE_D) {
      Structures.at(0).second.Rotate(2, -1);
    }
  }

  std::string tmp = "*this";
  Cameras[ActiveCamera].second->KeyPassthrough(event, key, tmp);
}

void RenderEngine::OnMouse(int event, int x, int y) {
  std::string tmp = "*this";
  Cameras[ActiveCamera].second->MousePassthrough(event, x, y, tmp);
}