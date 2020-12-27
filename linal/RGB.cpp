#include "RGB.h"

RGB::RGB() : R(0), G(0), B(0), A(0) {}

RGB::RGB(const int r, const int g, const int b) : R(r), G(g), B(b), A(0) {}
RGB::RGB(const int r, const int g, const int b, const int a)
    : R(r), G(g), B(b), A(a) {}

RGB::RGB(const RGB& rgb) : R(rgb.R), G(rgb.G), B(rgb.B), A(rgb.A) {}

RGB& RGB::operator=(RGB&& rgb) {
  RGB res = RGB(rgb.R, rgb.G, rgb.B, rgb.A);
  return res;
}
