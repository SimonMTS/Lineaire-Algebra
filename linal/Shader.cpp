#include "Shader.h"

Shader::Shader(int width, int height, const RGB& backgroundColor)
    : SDL2Wrapper(width, height, backgroundColor) {
}

void Shader::OnEvent(Renderer& renderer) { SDL2Wrapper::OnEvent(renderer); }

void Shader::SetBackground() { SDL2Wrapper::SetBackground(); }

void Shader::DrawLine(int ax, int ay, int bx, int by, const RGB& rgb) {
  SDL2Wrapper::DrawLine(ax, ay, bx, by, rgb);
}

void Shader::DrawPoint(int centreX, int centreY, int radius, const RGB& rgb) {
  //SDL2Wrapper::DrawPoint(centreX, centreY, radius, rgb);
}

void Shader::DrawSquare(int ax, int ay, int bx, int by, int cx, int cy,
                             int dx, int dy, const RGB& rgb) {
  //SDL2Wrapper::DrawLine(ax, ay, dx, dy, {255, 210, 210});
  //SDL2Wrapper::DrawLine(bx, by, cx, cy, {255, 210, 210});

  SDL2Wrapper::DrawLine(ax, ay, bx, by, {0, 0, 0});
  SDL2Wrapper::DrawLine(ax, ay, cx, cy, {0, 0, 0});
  SDL2Wrapper::DrawLine(dx, dy, bx, by, {0, 0, 0});
  SDL2Wrapper::DrawLine(dx, dy, cx, cy, {0, 0, 0});
}

void Shader::PushLines() {}
