#pragma once
#include <vector>
#include "Renderer.h"
#include "SDL2Wrapper.h"
#include "Point3D.h"
#include "Line3D.h"
using std::vector;

enum Perspective3D { Topview, Frontview, Sideview };

class Renderer3D : Renderer {
private:
    Perspective3D Perspective = Perspective3D::Frontview;

    const double GridStep = 10;
    double OriginX = 10;
    double OriginY = 10;
    double OriginZ = 10;

    unique_ptr<SDL2Wrapper> Sdl;
    vector<Line3D> Lines;

    void BeforeEach();
    void OnKey(int event, int key);
    void OnMouse(int event);
    void OnResize(int width, int height);

    void DrawGrid();
    void DrawLines();

    void Scale(const double x, const double y, const double z);
    void Move(const double x, const double y, const double z);

public:
    Renderer3D();
    void Init();

    void AddLine(const Line3D& l);
};

