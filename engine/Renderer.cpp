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
        if (Key_A) {
          cVector at90deg = {0, 1, 0};
          //at90deg = at90deg * cMatrix::GetRotationMatrix(3, Player.Rot);
          //std::cout << at90deg << "\n";
          Player.Dir = Player.Dir * cMatrix::GetRotationMatrix(at90deg, 3);
        }
        if (Key_D) {
          cVector at90deg = {0, 1, 0};
          //at90deg = at90deg * cMatrix::GetRotationMatrix(3, Player.Rot);
          //std::cout << at90deg << "\n";
          Player.Dir = Player.Dir * cMatrix::GetRotationMatrix(at90deg, -3);
        }

        if (Key_W) Player.Dir = Player.Dir * cMatrix::GetRotationMatrix(cVector{1, 0, 0}, -3);
        if (Key_S) Player.Dir = Player.Dir * cMatrix::GetRotationMatrix(cVector{1, 0, 0}, 3);

        if (Key_Q) Player.Rot = Player.Rot + 3;
        if (Key_E) Player.Rot = Player.Rot - 3;

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

void Renderer::AddStructure(const Structure& s) { Structures.push_back(s); }

void Renderer::AddCamera(const cVector& pos, unique_ptr<Camera> cam) {
  Cameras.push_back({pos, move(cam)});
}