#include "RenderEngine.h"

RenderEngine::RenderEngine() {
  int width = 600;
  int height = width;

  SDL_Init(SDL_INIT_VIDEO);
  RGB bgColor = RGB(255, 255, 255);
  Sdl = std::make_unique<SDL2Wrapper>(width, height, bgColor);

  OnResize(width, height);
}

void RenderEngine::Init() { Sdl->OnEvent(*this); }

void RenderEngine::AddLine(Line3D& l) { throw "dont"; }

void RenderEngine::AddCamera(Point3D pos, unique_ptr<Camera> cam) {
  Cameras.push_back({pos, move(cam)});
  ActiveCamera = Cameras.size() - 1;
}

void RenderEngine::OnResize(int width, int height) {
  OriginX = width / 2;
  OriginY = height / 2;
  OriginZ = 0;
}

void RenderEngine::DrawGrid() { Sdl->SetBackground(); }

void RenderEngine::BeforeEach() {
  DrawGrid();
  Cameras[ActiveCamera].second->DrawStructures();
}

void RenderEngine::OnKey(int event, int key) { std::cout << "key press\n"; }

void RenderEngine::OnMouse(int event) {
  // std::cout << "mouse\n";
}