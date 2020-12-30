#pragma once
#include <memory>
#include "SDL2Wrapper.h"
using std::unique_ptr;

class Shader : public SDL2Wrapper {
 public:
  Shader(int width, int height, const RGB& backgroundColor);

  void OnEvent(Renderer& renderer) override;

  void SetBackground() override;

  void DrawLine(int ax, int ay, int bx, int by, const RGB& rgb) override;

  void DrawPoint(int centreX, int centreY, int radius, const RGB& rgb) override;

  void PushLines();
};
