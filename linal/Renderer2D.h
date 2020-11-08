#pragma once
#include <vector>
#include "Renderer.h"
#include "SDL2Wrapper.h"
#include "Point2D.h"
#include "Line2D.h"
#include "Vector2D.h"
#include "Matrix2D.h"
using std::vector;

class Renderer2D : Renderer {
private:
    const double GridStep = 10;
    double OriginX = 10;
    double OriginY = 10;

    unique_ptr<SDL2Wrapper> Sdl;
    vector<Point2D> Points;
    vector<Vector2D> Vectors;
    vector<Line2D> Lines;

    void BeforeEach();
    void OnKey(int event, int key);
    void OnMouse(int event);
    void OnResize(int width, int height);

    void DrawGrid();
    void DrawPoints();
    void DrawVectors();
    void DrawLines();

public:
    Renderer2D();
    void Init();

    void AddVector(const Vector2D& v);
    void AddPoint(const Point2D& p);
    void AddLine(const Line2D& l);
};
