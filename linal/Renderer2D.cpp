#include "Renderer2D.h"

Renderer2D::Renderer2D() {
  int width = 640;
  int height = 480;

  SDL_Init(SDL_INIT_VIDEO);
  RGB bgColor = RGB(255, 255, 255);
  Sdl = std::make_unique<SDL2Wrapper>(width, height, bgColor);

  OriginX = (width / GridStep) / 2;
  OriginY = (height / GridStep) / 2;
  OriginX = ((int)OriginX);
  OriginY = ((int)OriginY);
}

void Renderer2D::Init() { Sdl->OnEvent(*this); }

void Renderer2D::AddPoint(const Point2D& p) { Points.push_back(p); }

void Renderer2D::AddVector(const Vector2D& v) { Vectors.push_back(v); }

void Renderer2D::AddLine(Line2D& l) { Lines.push_back(l); }

void Renderer2D::OnKey(int event, int key) {
  // std::cout << "key\n";
}

void Renderer2D::OnMouse(int event, int x, int y) {
  // std::cout << "mouse\n";
  if (event == SDL_MOUSEWHEEL + 100 || event == SDL_MOUSEWHEEL + 200) {
    std::cout << "mouse scroll\n";
    Matrix2D sm = Matrix2D::GetScalingMatrix(2, 2);
    Matrix2D tm1 = Matrix2D::GetTranslationMatrix(-2, -2);
    Matrix2D tm2 = Matrix2D::GetTranslationMatrix(2, 2);
    double angle = (event == SDL_MOUSEWHEEL + 100 ? 5.625 : -5.625);
    Matrix2D rm = Matrix2D::GetRotationMatrix(angle);
    Matrix2D cm = tm2 * rm * tm1;
    for (auto& line : Lines) {
      line.P1 = line.P1 * cm;
      line.P2 = line.P2 * cm;
    }
  }
}

void Renderer2D::OnResize(int width, int height) {
  OriginX = (width / GridStep) / 2;
  OriginY = (height / GridStep) / 2;
  OriginX = ((int)OriginX);
  OriginY = ((int)OriginY);
}

void Renderer2D::DrawGrid() {
  Sdl->SetBackground();
  RGB gridColor = RGB(245, 245, 245);
  RGB gridOriginColor = RGB(224, 224, 224);

  for (int x = 0; x < Sdl->Height; x += GridStep) {
    Sdl->DrawLine(0, x, Sdl->Width, x, gridColor);
  }
  for (int y = 0; y < Sdl->Width; y += GridStep) {
    Sdl->DrawLine(y, 0, y, Sdl->Height, gridColor);
  }
  Sdl->DrawLine(OriginX * GridStep, 0, OriginX * GridStep, Sdl->Height,
                gridOriginColor);
  Sdl->DrawLine(0, OriginY * GridStep, Sdl->Width, OriginY * GridStep,
                gridOriginColor);
}

void Renderer2D::DrawPoints() {
  RGB pointColor = RGB(66, 66, 66);
  for (auto& point : Points) {
    Sdl->DrawPoint(point.X * GridStep + (OriginX * GridStep),
                   point.Y * GridStep + (OriginY * GridStep), 4, pointColor);
  }
}

void Renderer2D::DrawVectors() {
  vector<RGB> vectorColors = {RGB(33, 150, 243), RGB(76, 175, 80),
                              RGB(255, 152, 0), RGB(156, 39, 176),
                              RGB(255, 235, 59)};

  int c = 0;
  for (auto& vect : Vectors) {
    Sdl->DrawLine(OriginX * GridStep, OriginY * GridStep,
                  vect.X * GridStep + (OriginX * GridStep),
                  vect.Y * GridStep + (OriginY * GridStep), vectorColors[c++]);
  }
}

void Renderer2D::DrawLines() {
  for (auto& line : Lines) {
    Sdl->DrawLine(line.P1.X * GridStep + (OriginX * GridStep),
                  line.P1.Y * GridStep + (OriginY * GridStep),
                  line.P2.X * GridStep + (OriginX * GridStep),
                  line.P2.Y * GridStep + (OriginY * GridStep),
                  RGB(33, 150, 243));
  }
}

void Renderer2D::BeforeEach() {
  DrawGrid();
  DrawPoints();
  DrawVectors();
  DrawLines();
}