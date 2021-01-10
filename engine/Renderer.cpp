#include "Renderer.hpp"

bool Renderer::show_helpline = false;
bool Renderer::show_orientation = false;
bool Renderer::show_AABB = false;
bool Renderer::show_camera_orientation = false;
bool Renderer::dark_mode = false;

Renderer::Renderer(const Structure& p) : Player(p) {
  SDL_Init(SDL_INIT_VIDEO);
  Drawer = std::make_unique<SDL2Wrapper>(600, 600, RGB(255, 255, 255));
}

void Renderer::Init() {
  Drawer->OnEvent([this](const int type, const int d1, const int d2) {
    // before each frame
    if (type == -2) {
      // Call per tick actions
      Player.ExecutePerTickAction(Tick, *this);
      for (auto& structure : Structures) {
        structure.ExecutePerTickAction(Tick, *this);
      }
      Tick = Tick == 100 ? 1 : Tick + 1;

      {  // Update player position
        cVector fw = {0, 0, 1};
        fw = fw * Speed;
        Player.State *= cMatrix::GetTranslationMatrix(fw.X, fw.Y, fw.Z);
      }
      Speed *= 0.97;
      Speed = Speed < 0.2 ? 0 : Speed;

      {  // Detect collisions
        // doing this without a raw pointer would have been a lot more work
        vector<Structure*> all_structs_inc_player;
        all_structs_inc_player.push_back(&Player);
        for (auto& structure : Structures) {
          all_structs_inc_player.push_back(&structure);
        }

        for (auto structure : all_structs_inc_player) {
          structure->CalcAABB();
        }

        for (auto& s1 : all_structs_inc_player) {
          bool s1_any_coll = false;
          for (auto& s2 : all_structs_inc_player) {
            s1_any_coll = s1->IsCollidingWith(*s2) ? true : s1_any_coll;
          }
          s1->WasCollidingLastCheck = s1_any_coll;
        }
      }

      // Execute callbacks for active keys
      for (const auto& [key, onKeyCallback] : OnKeyCallbacks) {
        if (onKeyCallback.first) {
          onKeyCallback.second(*this);
        }
      }
      Cameras[ActiveCamera]->CallKeyCallbacks();
      Cameras[0]->CallKeyCallbacks();

      // Render structures
      if (Dead == 0) {
        Drawer->SetBackground(dark_mode ? RGB{21, 21, 21} : RGB{255, 255, 255});
        Cameras[ActiveCamera]->DrawGrid(*Drawer, dark_mode);
        Cameras[ActiveCamera]->DrawStructures(*Drawer, Structures, Cameras,
                                              dark_mode);
        vector<Structure> p = {Player};
        Cameras[ActiveCamera]->DrawStructures(*Drawer, p, Cameras, dark_mode);
      } else {
        Dead--;
        RGB color = Won ? RGB{76, 175, 80} : RGB{244, 67, 54};
        Drawer->SetBackground(color);
      }
    }

    // key up/down event
    if ((type == -3 || type == -4) &&
        OnKeyCallbacks.find(d2) != OnKeyCallbacks.end()) {
      OnKeyCallbacks[d2].first = type == -4;
    } else if (type == -3 || type == -4) {
      Cameras[ActiveCamera]->HandleKeyEvent(type, d1, d2);
      Cameras[0]->HandleKeyEvent(type, d1, d2);
    }

    // mouse events
    if (type == 1024 || type == 1025 || type == 1026 || type == 1027) {
      Cameras[ActiveCamera]->HandleMouseEvent(type, d1, d2);
    }

    // Game mechanics
    {
      if (Player.WasCollidingLastCheck) {
        Player.State = cMatrix::GetIdentityMatrix();
        Speed = 0;

        Structures.clear();
        Adder::AddGoals(*this);
        Dead = 60;
        Won = false;
      }

      for (auto& structure : Structures) {
        if (structure.WasCollidingLastCheck) {
          Structures.erase(
              std::remove(Structures.begin(), Structures.end(), structure),
              Structures.end());
        }
      }

      if (Structures.size() == 0 || Structures.at(0).Components.size() == 1) {
        Player.State = cMatrix::GetIdentityMatrix();
        Speed = 0;

        Structures.clear();
        Adder::AddGoals(*this);
        Dead = 60;
        Won = true;
      }
    }
  });
}

void Renderer::OnKey(const int key,
                     const function<void(Renderer& r)>& callback) {
  OnKeyCallbacks[key] = {false, callback};
}

void Renderer::AddStructure(const Structure& s) { Structures.push_back(s); }

void Renderer::AddCamera(unique_ptr<Camera> cam) {
  Cameras.push_back(move(cam));
}