#pragma once
#include <functional>
#include <iostream>

#include "../SDL2/include/SDL.h"
#undef main
#include "RGB.hpp"
using std::function;
using std::unique_ptr;

class SDL2Wrapper {
 protected:
  unique_ptr<SDL_Window, void (*)(SDL_Window*)> SDLWindow;
  unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> SDLRenderer;

  bool Running = true;

  unique_ptr<SDL_Window, void (*)(SDL_Window*)> InitWindow(const int width,
                                                           const int height);
  unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> InitRenderer();

 public:
  int Width;
  int Height;
  RGB BackgroundColor;

  SDL2Wrapper(const int width, const int height, const RGB& backgroundColor);
  ~SDL2Wrapper();

  void OnEvent(const function<void(const int, const int, const int)>& callback);

  void SetBackground();

  void DrawLine(const int ax, const int ay, const int bx, const int by,
                const RGB& rgb);

  void DrawSquare(const int ax, const int ay, const int bx, const int by,
                  const int cx, const int cy, const int dx, const int dy,
                  const RGB& rgb);
};
