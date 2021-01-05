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
      // Update player position
      {
        cVector fw = {0, 0, 1};
        fw = fw * Speed;
        Player.State =
            Player.State *
                       cMatrix::GetTranslationMatrix(fw.X, fw.Y, fw.Z);
      }
      Speed *= 0.97;
      Speed = Speed < 0.2 ? 0 : Speed;

      // Execute callbacks for active keys
      for (const auto& [key, onKeyCallback] : OnKeyCallbacks) {
        if (onKeyCallback.first) {
          onKeyCallback.second(onKeyCallback.first, d2, *this);
        }
      }

      // Render structures
      Drawer->SetBackground();
      Cameras[ActiveCamera].second->DrawGrid(*Drawer,
                                             Cameras[ActiveCamera].first);
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

    // key up/down event
    if ((type == -3 || type == -4) &&
        OnKeyCallbacks.find(d2) != OnKeyCallbacks.end()) {
      OnKeyCallbacks[d2].first = type == -4;
    }

    // mouse events
    if (type == 1024 || type == 1025 || type == 1026 || type == 1027) {
      // not very neat yet
      Cameras[ActiveCamera].first =
          Cameras[ActiveCamera].first +
          Cameras[ActiveCamera].second->HandleMouseEvent(type, d1, d2);
    }
  });
}

void Renderer::OnResize(const int width, const int height) {
  OriginX = width / 2;
  OriginY = height / 2;
  OriginZ = 0;
}

void Renderer::OnKey(const int key,
                     const function<void(const bool down, const int key,
                                         Renderer& r)>& callback) {
  OnKeyCallbacks[key] = {false, callback};
}

void Renderer::OnMouse(const function<void()>& callback) {}

void Renderer::AddStructure(const Structure& s) { Structures.push_back(s); }

void Renderer::AddCamera(const cVector& pos, unique_ptr<Camera> cam) {
  Cameras.push_back({pos, move(cam)});
}