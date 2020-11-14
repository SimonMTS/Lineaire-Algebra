#pragma once
#include "Renderer.h"
#include "SDL2Wrapper.h"
#include "Line3D.h"

class rendererPerspective : public Renderer {
private:
    const double GridStep = 1;
    double OriginX = 1;
    double OriginY = 1;
    double OriginZ = 1;

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
    void Rotate(const int dir);

public:
    rendererPerspective();
    void Init();

    void AddLine(Line3D& l) override;
};

