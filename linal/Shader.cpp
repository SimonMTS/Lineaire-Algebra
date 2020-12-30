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
  //for (size_t a = ax; a < cx; a++) {
  //  SDL2Wrapper::DrawLine(a, ay, bx, by, {100, 100, 100});
  //}
  //for (size_t d = cx; d < dx; d++) {
  //  SDL2Wrapper::DrawLine(d, dy, bx, by, {100, 100, 100});
  //}
  //for (size_t b = ax; b < bx; b++) {
  //  SDL2Wrapper::DrawLine(b, ay, cx, cy, {100, 100, 100});
  //}
  //for (size_t c = cx; c < dx; c++) {
  //  SDL2Wrapper::DrawLine(c, dy, bx, by, {100, 100, 100});
  //}

  //for (size_t a = bx; a < ax; a++) {
  //  for (size_t c = dx; c < cx; c++) {
  //    SDL2Wrapper::DrawLine(a, ay, c, cy, {100, 100, 100});
  //  }
  //}

  //{
  //  int delta_x = cx - ax;
  //  int delta_y = cy - ay;

  //  for (size_t x = ax; x < cx; x++) {
  //    int y = ay + delta_y * (x - ax) / delta_x;
  //    SDL2Wrapper::DrawPoint(x, y, 2, {100, 100, 100});
  //  }
  //}

  SDL2Wrapper::DrawLine(ax, ay, bx, by, rgb);
  SDL2Wrapper::DrawLine(ax, ay, cx, cy, rgb);
  SDL2Wrapper::DrawLine(dx, dy, bx, by, rgb);
  SDL2Wrapper::DrawLine(dx, dy, cx, cy, rgb);

  // Sdl.DrawLine(p1.X, p1.Y, p4.X, p4.Y, color);
  // Sdl.DrawLine(p2.X, p2.Y, p3.X, p3.Y, color);
}

void Shader::PushLines() {}
