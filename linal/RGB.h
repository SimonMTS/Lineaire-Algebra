#pragma once

class RGB {
public:
    const int R;
    const int G;
    const int B;
    const int A;

    RGB();
    RGB(const int r, const int g, const int b);
    RGB(const int r, const int g, const int b, const int a);
    RGB(const RGB& rgb);
    RGB& operator= (RGB&& rgb);
};

