#include "Renderer.hpp"

Renderer::Renderer(const Structure& p) {
  int width = 600;
  int height = width;

  SDL_Init(SDL_INIT_VIDEO);
  RGB bgColor = RGB(255, 255, 255);
  Drawer = std::make_unique<Shader>(width, height, bgColor);

  OnResize(width, height);

  Player = p;
}

void Renderer::Init() {
  Drawer->OnEvent([this](const int type, const int d1, const int d2) {
    // before each frame
    if (type == -2) {
      { // move player
        if (Key_A) Player.Dir = Player.Dir * cMatrix::GetRotationMatrix(2, -1);
        if (Key_D) Player.Dir = Player.Dir * cMatrix::GetRotationMatrix(2, 1);

        Player.Pos = Player.Pos + (Player.Dir * Speed);
        Speed = Key_Shift ? Speed + 0.5 : Speed * 0.97;

        if (Speed > 5) Speed = 5;
        if (Speed < 0.1) Speed = 0;
      }

      Drawer->SetBackground();
      Cameras[ActiveCamera].second->DrawGrid(*Drawer, Cameras[ActiveCamera].first);
      Cameras[ActiveCamera].second->DrawStructures(*Drawer, Structures,
                                                   Cameras[ActiveCamera].first);
      vector<Structure> p = {Player};
      Cameras[ActiveCamera].second->DrawStructures(*Drawer, p,
                                                   Cameras[ActiveCamera].first);
    }

    // resize event
    if (type == -1) {
      OnResize(d1, d2);
    }

    // key up event
    if (type == -3) {
      for (const auto& c : OnKeyCallbacks) {
        c(false, d2, *this);
      }
    }

    // key down event
    if (type == -4) {
      for (const auto& c : OnKeyCallbacks) {
        c(true, d2, *this);
      }
    }


  });
}

void Renderer::OnResize(const int width, const int height) {
  OriginX = width / 2;
  OriginY = height / 2;
  OriginZ = 0;
}

void Renderer::OnKey(const function<void(const bool down, const int key,
                                         Renderer& r)>& callback) {
  OnKeyCallbacks.push_back(callback);
}

void Renderer::OnMouse(const function<void()>& callback) {}

void Renderer::AddCamera(const cVector& pos, unique_ptr<Camera> cam) {
  Cameras.push_back({pos, move(cam)});
}