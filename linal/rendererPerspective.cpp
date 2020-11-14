#include "rendererPerspective.h"

rendererPerspective::rendererPerspective() {
    int width = 600;
    int height = width;

    SDL_Init(SDL_INIT_VIDEO);
    RGB bgColor = RGB(255, 255, 255);
    Sdl = std::make_unique<SDL2Wrapper>(width, height, bgColor);

    OnResize(width, height);
}

void rendererPerspective::Init() {
    Sdl->OnEvent(*this);
}

void rendererPerspective::AddLine(Line3D& l) {
    Lines.push_back(l);
}

//void rendererPerspective::OnKey(int event, int key) {
//    //std::cout << "key press\n";
//}

void rendererPerspective::OnMouse(int event) {
    //std::cout << "mouse\n";
}

void rendererPerspective::OnResize(int width, int height) {
    OriginX = 350;
    OriginY = 350;
    OriginZ = 350;
}

void rendererPerspective::DrawGrid() {
    Sdl->SetBackground();
}

void rendererPerspective::DrawLines() {
    RGB color = RGB(0, 0, 0);

    for (auto& line : Lines) {
        Point3D p1 = line.P1;
        Point3D p2 = line.P2;

        Matrix3D pm = Matrix3D::GetProjectionMatrix(1, 20, 80);

        p1 = p1 * pm;
        p2 = p2 * pm;

        p1.X = (Sdl->Width / 2) + ((p1.X / p1.W) * (Sdl->Width / p1.W));
        p1.Y = (Sdl->Height / 2) + ((p1.Y / p1.W) * (Sdl->Height / p1.W));

        p2.X = (Sdl->Width / 2) + ((p2.X / p2.W) * (Sdl->Width / p2.W));
        p2.Y = (Sdl->Height / 2) + ((p2.Y / p2.W) * (Sdl->Height / p2.W));

        double startFrameX = p1.X * GridStep + (OriginX * GridStep);
        double startFrameY = p1.Y * GridStep + (OriginY * GridStep);
        double endFrameX = p2.X * GridStep + (OriginX * GridStep);
        double endFrameY = p2.Y * GridStep + (OriginY * GridStep);

        Sdl->DrawLine(
            startFrameX,
            startFrameY,
            endFrameX,
            endFrameY,
            color);
    }
}

void rendererPerspective::BeforeEach() {
    DrawGrid();
    DrawLines();
}

void rendererPerspective::OnKey(int event, int key) {
    std::cout << "key press\n";

    if (event == SDL_KEYUP && key == SDL_SCANCODE_Z) { Scale(2, 2, 2); std::cout << "Scale up\n"; }
    if (event == SDL_KEYUP && key == SDL_SCANCODE_X) { Scale(0.5, 0.5, 0.5); std::cout << "Scale down\n"; }

    if (event == SDL_KEYUP && key == SDL_SCANCODE_RIGHT) { Move(1, 0, 0); std::cout << "Move +x\n"; }
    if (event == SDL_KEYUP && key == SDL_SCANCODE_LEFT) { Move(-1, 0, 0); std::cout << "Move -x\n"; }

    if (event == SDL_KEYUP && key == SDL_SCANCODE_UP) { Move(0, 0, 1); std::cout << "Move +z\n"; }
    if (event == SDL_KEYUP && key == SDL_SCANCODE_DOWN) { Move(0, 0, -1); std::cout << "Move -z\n"; }

    if (event == SDL_KEYUP && key == SDL_SCANCODE_PAGEUP) { Move(0, 1, 0); std::cout << "Move +y\n"; }
    if (event == SDL_KEYUP && key == SDL_SCANCODE_PAGEDOWN) { Move(0, -1, 0); std::cout << "Move -y\n"; }

    if (event == SDL_KEYUP && key == SDL_SCANCODE_KP_1) { Rotate(1); std::cout << "Rotate +x\n"; }
    if (event == SDL_KEYUP && key == SDL_SCANCODE_KP_3) { Rotate(-1); std::cout << "Rotate -x\n"; }

    if (event == SDL_KEYUP && key == SDL_SCANCODE_KP_4) { Rotate(2); std::cout << "Rotate +y\n"; }
    if (event == SDL_KEYUP && key == SDL_SCANCODE_KP_6) { Rotate(-2); std::cout << "Rotate -y\n"; }

    if (event == SDL_KEYUP && key == SDL_SCANCODE_KP_7) { Rotate(3); std::cout << "Rotate +z\n"; }
    if (event == SDL_KEYUP && key == SDL_SCANCODE_KP_9) { Rotate(-3); std::cout << "Rotate -z\n"; }

    if (event == SDL_KEYUP && key == SDL_SCANCODE_KP_0) { Rotate(1); Rotate(2); Rotate(3); std::cout << "Rotate all axis\n"; }
}

void rendererPerspective::Scale(const double x, const double y, const double z) {
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

void rendererPerspective::Move(const double x, const double y, const double z) {
    Matrix3D tm = Matrix3D::GetTranslationMatrix(x, y, z);
    for (auto& line : Lines) {
        line.P1 = line.P1 * tm;
        line.P2 = line.P2 * tm;
    }
}

void rendererPerspective::Rotate(const int dir) {
    Point3D localOrigin = Lines.at(0).P1;

    Matrix3D tm1 = Matrix3D::GetTranslationMatrix((-localOrigin.X), (-localOrigin.Y), (-localOrigin.Z));
    Matrix3D tm2 = Matrix3D::GetTranslationMatrix(localOrigin.X, localOrigin.Y, localOrigin.Z);
    Matrix3D rm = Matrix3D::GetRotationMatrix(abs(dir), (dir > 0 ? 5.625 : -5.625));
    Matrix3D cm = tm2 * rm * tm1;

    for (auto& line : Lines) {
        line.P1 = line.P1 * cm;
        line.P2 = line.P2 * cm;
    }
}
