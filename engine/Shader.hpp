#pragma once
#include <memory>

#include "SDL2Wrapper.hpp"
using std::pair;
using std::unique_ptr;

class Shader : public SDL2Wrapper {
 public:
  Shader(int width, int height, const RGB& backgroundColor);

  void DrawSquare(int ax, int ay, int bx, int by, int cx, int cy, int dx,
                  int dy, const RGB& rgb) override;

  void PushLines();
};
