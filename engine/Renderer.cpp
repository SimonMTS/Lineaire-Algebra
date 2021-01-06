#include "Renderer.hpp"

Renderer::Renderer(const Structure& p) : Player(p) {
  SDL_Init(SDL_INIT_VIDEO);
  Drawer = std::make_unique<Shader>(600, 600, RGB(255, 255, 255));
}

void Renderer::Init() {
  Drawer->OnEvent([this](const int type, const int d1, const int d2) {
    // before each frame
    if (type == -2) {
      {  // Update player position
        cVector fw = {0, 0, 1};
        fw = fw * Speed;
        Player.State =
            Player.State * cMatrix::GetTranslationMatrix(fw.X, fw.Y, fw.Z);
      }
      Speed *= 0.97;
      Speed = Speed < 0.2 ? 0 : Speed;

      // Execute callbacks for active keys
      for (const auto& [key, onKeyCallback] : OnKeyCallbacks) {
        if (onKeyCallback.first) {
          onKeyCallback.second(onKeyCallback.first, d2, *this);
        }
      }
      Cameras[ActiveCamera]->CallKeyCallbacks();

      // Render structures
      Drawer->SetBackground();
      Cameras[ActiveCamera]->DrawGrid(*Drawer);
      Cameras[ActiveCamera]->DrawStructures(*Drawer, Structures);
      vector<Structure> p = {Player};
      Cameras[ActiveCamera]->DrawStructures(*Drawer, p);
    }

    // key up/down event
    if ((type == -3 || type == -4) &&
        OnKeyCallbacks.find(d2) != OnKeyCallbacks.end()) {
      OnKeyCallbacks[d2].first = type == -4;
    } else if (type == -3 || type == -4) {
      Cameras[ActiveCamera]->HandleKeyEvent(type, d1, d2);
    }

    // mouse events
    if (type == 1024 || type == 1025 || type == 1026 || type == 1027) {
      Cameras[ActiveCamera]->HandleMouseEvent(type, d1, d2);
    }
  });
}

void Renderer::OnKey(const int key,
                     const function<void(const bool down, const int key,
                                         Renderer& r)>& callback) {
  OnKeyCallbacks[key] = {false, callback};
}

void Renderer::AddStructure(const Structure& s) { Structures.push_back(s); }

void Renderer::AddCamera(unique_ptr<Camera> cam) {
  Cameras.push_back(move(cam));
}