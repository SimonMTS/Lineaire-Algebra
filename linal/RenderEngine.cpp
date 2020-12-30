#include "RenderEngine.h"

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
  Structures.at(0).second.Rotate(1);
  Structures.at(0).second.Rotate(2);
  Structures.at(0).second.Rotate(3);

  // Structures.at(0).second.Objects.at(1).second.Rotate(1);

  DrawGrid();
  Cameras[ActiveCamera].second->DrawGrid(*Sdl, Cameras[ActiveCamera].first);
  Cameras[ActiveCamera].second->DrawStructures(*Sdl, Structures,
                                               Cameras[ActiveCamera].first);
  Sdl->PushLines();
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
}

void RenderEngine::OnMouse(int event, int x, int y) {
  if (event == SDL_MOUSEBUTTONDOWN) {
    IsDragging = {true, x, y};
  }
  if (event == SDL_MOUSEBUTTONUP) {
    IsDragging = {false, 0, 0};
  }
  if (event == SDL_MOUSEMOTION && get<0>(IsDragging)) {
    Cameras[ActiveCamera].first.X += x - get<1>(IsDragging);
    Cameras[ActiveCamera].first.Y -= y - get<2>(IsDragging);

    IsDragging = {true, x, y};
  }
  if (event == SDL_MOUSEWHEEL + 100 || event == SDL_MOUSEWHEEL + 200) {
    Cameras[ActiveCamera].first.Z -= y * 10;
  }
}