#include "SDL2Wrapper.hpp"

unique_ptr<SDL_Window, void (*)(SDL_Window*)> SDL2Wrapper::InitWindow(
    int width, int height) {
  return unique_ptr<SDL_Window, void (*)(SDL_Window*)>(
      SDL_CreateWindow("LINAL2D", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, width, height,
                       SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE),
      SDL_DestroyWindow);
}

unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> SDL2Wrapper::InitRenderer() {
  return unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>(
      SDL_CreateRenderer(SDLWindow.get(), -1,
                         SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
      SDL_DestroyRenderer);
}

SDL2Wrapper::SDL2Wrapper(int width, int height, const RGB& backgroundColor)
    : Width(width),
      Height(height),
      SDLWindow(InitWindow(width, height)),
      SDLRenderer(InitRenderer()) {
  // SDL_RenderSetScale(SDLRenderer.get(), 2.0f, 2.0f);
  // SDL_SetRelativeMouseMode(SDL_TRUE);
  SetBackground(backgroundColor);
  SDL_RenderPresent(SDLRenderer.get());
}

SDL2Wrapper::~SDL2Wrapper() { SDL_Quit(); }

void SDL2Wrapper::OnEvent(
    const function<void(const int, const int, const int)>& callback) {
  while (Running) {
    callback(-2, -2, -2);
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          Running = false;
          break;
        case SDL_WINDOWEVENT:
          if (event.window.event != SDL_WINDOWEVENT_SIZE_CHANGED) break;
          Width = event.window.data1;
          Height = event.window.data2;
          callback(-1, Width, Height);
          break;

        case SDL_KEYUP:
          callback(-3, SDL_KEYUP, event.key.keysym.scancode);
          break;
        case SDL_KEYDOWN:
          callback(-4, SDL_KEYDOWN, event.key.keysym.scancode);
          break;

        case SDL_MOUSEMOTION:
          callback(SDL_MOUSEMOTION, event.motion.x, event.motion.y);
          break;
        case SDL_MOUSEBUTTONDOWN:
          callback(SDL_MOUSEBUTTONDOWN, event.button.x, event.button.y);
          break;
        case SDL_MOUSEBUTTONUP:
          callback(SDL_MOUSEBUTTONUP, event.button.x, event.button.y);
          break;
        case SDL_MOUSEWHEEL:
          callback(SDL_MOUSEWHEEL, event.wheel.x, event.wheel.y);
          break;
      }
    }
    SDL_RenderPresent(SDLRenderer.get());
  }
}

void SDL2Wrapper::SetBackground(const RGB& backgroundColor) {
  SDL_SetRenderDrawColor(SDLRenderer.get(), backgroundColor.R,
                         backgroundColor.G, backgroundColor.B,
                         backgroundColor.A);
  SDL_Rect rect;
  rect.x = rect.y = 0;
  rect.w = Width;
  rect.h = Height;
  SDL_RenderFillRect(SDLRenderer.get(), &rect);
}

void SDL2Wrapper::DrawLine(const int ax, const int ay, const int bx,
                           const int by, const RGB& rgb) {
  const int sdl_ax = ax;
  const int sdl_ay = Height - ay;
  const int sdl_bx = bx;
  const int sdl_by = Height - by;

  SDL_SetRenderDrawColor(SDLRenderer.get(), rgb.R, rgb.G, rgb.B, rgb.A);
  SDL_RenderDrawLine(SDLRenderer.get(), sdl_ax, sdl_ay, sdl_bx, sdl_by);
}

void SDL2Wrapper::DrawSquare(int ax, int ay, int bx, int by, int cx, int cy,
                             int dx, int dy, const RGB& rgb) {
  // SDL2Wrapper::DrawLine(ax, ay, dx, dy, {255, 210, 210});
  // SDL2Wrapper::DrawLine(bx, by, cx, cy, {255, 210, 210});

  SDL2Wrapper::DrawLine(ax, ay, bx, by, rgb);
  SDL2Wrapper::DrawLine(ax, ay, cx, cy, rgb);
  SDL2Wrapper::DrawLine(dx, dy, bx, by, rgb);
  SDL2Wrapper::DrawLine(dx, dy, cx, cy, rgb);
}