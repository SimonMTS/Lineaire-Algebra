#pragma once
#include <SDL.h>

#include <functional>
#include <iostream>
#undef main
#include "RGB.h"
#include "Renderer.h"
using std::function;
using std::unique_ptr;

class SDL2Wrapper {
 private:
  unique_ptr<SDL_Window, void (*)(SDL_Window*)> SDLWindow;
  unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> SDLRenderer;

  bool Running = true;

  unique_ptr<SDL_Window, void (*)(SDL_Window*)> InitWindow(int width,
                                                           int height);
  unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> InitRenderer();

 public:
  int Width;
  int Height;
  RGB BackgroundColor;

  SDL2Wrapper(int width, int height, const RGB& backgroundColor);
  ~SDL2Wrapper();

  virtual void OnEvent(Renderer& renderer);

  virtual void SetBackground();

  virtual void DrawLine(int ax, int ay, int bx, int by, const RGB& rgb);

  virtual void DrawPoint(int centreX, int centreY, int radius, const RGB& rgb);
};
