#include "Shader.hpp"

Shader::Shader(int width, int height, const RGB& backgroundColor)
    : SDL2Wrapper(width, height, backgroundColor) {}

void Shader::DrawSquare(int ax, int ay, int bx, int by, int cx, int cy, int dx,
                        int dy, const RGB& rgb) {
  // SDL2Wrapper::DrawLine(ax, ay, dx, dy, {255, 210, 210});
  // SDL2Wrapper::DrawLine(bx, by, cx, cy, {255, 210, 210});

  SDL2Wrapper::DrawLine(ax, ay, bx, by, rgb);
  SDL2Wrapper::DrawLine(ax, ay, cx, cy, rgb);
  SDL2Wrapper::DrawLine(dx, dy, bx, by, rgb);
  SDL2Wrapper::DrawLine(dx, dy, cx, cy, rgb);
}

void Shader::PushLines() {}
