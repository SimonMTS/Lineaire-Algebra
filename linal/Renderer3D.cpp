#include "Renderer3D.h"

Renderer3D::Renderer3D() {
    int width = 600;
    int height = width;

    SDL_Init(SDL_INIT_VIDEO);
    RGB bgColor = RGB(255, 255, 255);
    Sdl = std::make_unique<SDL2Wrapper>(width, height, bgColor);

    OnResize(width, height);
}

void Renderer3D::Init() {
    Sdl->OnEvent(*this);
}

void Renderer3D::AddLine(const Line3D& l) {
    Lines.push_back(l);
}

void Renderer3D::OnKey(int event, int key) {
    std::cout << "key press\n";
    if (key == SDL_SCANCODE_A) { Perspective = Perspective3D::Frontview; std::cout << "Front view\n"; }
    if (key == SDL_SCANCODE_S) { Perspective = Perspective3D::Topview; std::cout << "Top view\n"; }
    if (key == SDL_SCANCODE_D) { Perspective = Perspective3D::Sideview; std::cout << "Side view\n"; }

    if (event == SDL_KEYUP && key == SDL_SCANCODE_Z) { Scale(2, 2, 2); std::cout << "Scale up\n"; }
    if (event == SDL_KEYUP && key == SDL_SCANCODE_X) { Scale(0.5, 0.5, 0.5); std::cout << "Scale down\n"; }

    if (event == SDL_KEYUP && key == SDL_SCANCODE_RIGHT) { Move(1, 0, 0); std::cout << "Move +x\n"; }
    if (event == SDL_KEYUP && key == SDL_SCANCODE_LEFT) { Move(-1, 0, 0); std::cout << "Move -x\n"; }

    if (event == SDL_KEYUP && key == SDL_SCANCODE_UP) { Move(0, 0, 1); std::cout << "Move +z\n"; }
    if (event == SDL_KEYUP && key == SDL_SCANCODE_DOWN) { Move(0, 0, -1); std::cout << "Move -z\n"; }

    if (event == SDL_KEYUP && key == SDL_SCANCODE_PAGEUP) { Move(0, 1, 0); std::cout << "Move +y\n"; }
    if (event == SDL_KEYUP && key == SDL_SCANCODE_PAGEDOWN) { Move(0, -1, 0); std::cout << "Move -y\n"; }
}

void Renderer3D::OnMouse(int event) {
    //std::cout << "mouse\n";
}

void Renderer3D::OnResize(int width, int height) {
    //OriginX = ((width / 2) / GridStep) / 2;
    //OriginY = ((height / 2) / GridStep) / 2;
    //OriginZ = (((Perspective == Perspective3D::Topview ? width : height) / 2) / GridStep) / 2;
    OriginX = 4; // ((int)OriginX);
    OriginY = 4; // ((int)OriginY);
    OriginZ = 4; // ((int)OriginZ);
}

void Renderer3D::DrawGrid() {
    Sdl->SetBackground();
    RGB gridColor = RGB(245, 245, 245);

    RGB gridOriginColor = RGB(224, 224, 224);
    RGB colorX = RGB(255, 152, 0);
    RGB colorY = RGB(33, 150, 243);
    RGB colorZ = RGB(76, 175, 80);

    for (int x = 0; x < Sdl->Height; x += GridStep) {
        Sdl->DrawLine(0, x, Sdl->Width, x, gridColor);
    }
    for (int y = 0; y < Sdl->Width; y += GridStep) {
        Sdl->DrawLine(y, 0, y, Sdl->Height, gridColor);
    }
    Sdl->DrawLine(OriginX * GridStep, 0, OriginX * GridStep, Sdl->Height, gridOriginColor);
    Sdl->DrawLine(0, OriginY * GridStep, Sdl->Width, OriginY * GridStep, gridOriginColor);
}

void Renderer3D::DrawLines() {
    for (auto& line : Lines) {
        double startFrameX = 0;
        double startFrameY = 0;
        double endFrameX = 0;
        double endFrameY = 0;
        RGB color = RGB(0, 0, 0);

        if (Perspective == Perspective3D::Frontview) {
            startFrameX = line.P1.X * GridStep + (OriginX * GridStep);
            startFrameY = line.P1.Y * GridStep + (OriginY * GridStep);
            endFrameX = line.P2.X * GridStep + (OriginX * GridStep);
            endFrameY = line.P2.Y * GridStep + (OriginY * GridStep);
        } else if (Perspective == Perspective3D::Topview) {
            startFrameX = line.P1.X * GridStep + (OriginX * GridStep);
            startFrameY = line.P1.Z * GridStep + (OriginZ * GridStep);
            endFrameX = line.P2.X * GridStep + (OriginX * GridStep);
            endFrameY = line.P2.Z * GridStep + (OriginZ * GridStep);
        } else if (Perspective == Perspective3D::Sideview) {
            startFrameX = line.P1.Z * GridStep + (OriginZ * GridStep);
            startFrameY = line.P1.Y * GridStep + (OriginY * GridStep);
            endFrameX = line.P2.Z * GridStep + (OriginZ * GridStep);
            endFrameY = line.P2.Y * GridStep + (OriginY * GridStep);
        }

        Sdl->DrawLine(
            startFrameX,
            startFrameY,
            endFrameX,
            endFrameY,
            color);
    }
}

void Renderer3D::Scale(const double x, const double y, const double z) {
    Point3D localOrigin = Lines.at(0).P1;

    Matrix3D tm1 = Matrix3D::GetTranslationMatrix((-localOrigin.X), (-localOrigin.Y), (-localOrigin.Z));
    Matrix3D tm2 = Matrix3D::GetTranslationMatrix(localOrigin.X, localOrigin.Y, localOrigin.Z);
    Matrix3D sm = Matrix3D::GetScalingMatrix(x, y, z);
    Matrix3D cm = tm2 * sm * tm1;

    for (auto& line : Lines) {
        line.P1 = line.P1 * cm;
        line.P2 = line.P2 * cm;
    }
}

void Renderer3D::Move(const double x, const double y, const double z) {
    Matrix3D tm = Matrix3D::GetTranslationMatrix(x, y, z);
    for (auto& line : Lines) {
        line.P1 = line.P1 * tm;
        line.P2 = line.P2 * tm;
    }
}

void Renderer3D::BeforeEach() {
    DrawGrid();
    DrawLines();
}