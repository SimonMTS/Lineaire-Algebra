#include "rendererPerspective.h"

rendererPerspective::rendererPerspective() {
  int width = 600;
  int height = width;

  SDL_Init(SDL_INIT_VIDEO);
  RGB bgColor = RGB(255, 255, 255);
  Sdl = std::make_unique<SDL2Wrapper>(width, height, bgColor);

  OnResize(width, height);
}

void rendererPerspective::Init() { Sdl->OnEvent(*this); }

void rendererPerspective::AddLine(Line3D& l) { Lines.push_back(l); }

void rendererPerspective::AddCamera(Point3D pos, int type) {
  Cameras.push_back({pos, type});
  ActiveCamera = Cameras.back();
}

// void rendererPerspective::OnKey(int event, int key) {
//    //std::cout << "key press\n";
//}

void rendererPerspective::OnMouse(int event, int x, int y) {
  // std::cout << "mouse\n";
}

void rendererPerspective::OnResize(int width, int height) {
  OriginX = width / 2;
  OriginY = height / 2;
  OriginZ = 0;
}

void rendererPerspective::DrawGrid() {
  Sdl->SetBackground();

  if (ActiveCamera.second == 0) {
    const double GridStep = 20;

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
    Sdl->DrawLine(5 * GridStep, 0, 5 * GridStep, Sdl->Height, gridOriginColor);
    Sdl->DrawLine(0, 5 * GridStep, Sdl->Width, 5 * GridStep, gridOriginColor);
  }
}

void rendererPerspective::DrawLines() {
  if (ActiveCamera.second == 0) {
    const double GridStep = 20;
    for (auto& line : Lines) {
      double startFrameX = 0;
      double startFrameY = 0;
      double endFrameX = 0;
      double endFrameY = 0;
      RGB color = RGB(0, 0, 0);

      // if (Perspective == Perspective3D::Frontview) {
      //  startFrameX = line.P1.X * GridStep + (OriginX * GridStep);
      //  startFrameY = line.P1.Y * GridStep + (OriginY * GridStep);
      //  endFrameX = line.P2.X * GridStep + (OriginX * GridStep);
      //  endFrameY = line.P2.Y * GridStep + (OriginY * GridStep);
      //} else if (Perspective == Perspective3D::Topview) {
      startFrameX = line.P1.X * GridStep + (5 * GridStep);
      startFrameY = line.P1.Z * GridStep + (5 * GridStep);
      endFrameX = line.P2.X * GridStep + (5 * GridStep);
      endFrameY = line.P2.Z * GridStep + (5 * GridStep);
      //} else if (Perspective == Perspective3D::Sideview) {
      //  startFrameX = line.P1.Z * GridStep + (OriginZ * GridStep);
      //  startFrameY = line.P1.Y * GridStep + (OriginY * GridStep);
      //  endFrameX = line.P2.Z * GridStep + (OriginZ * GridStep);
      //  endFrameY = line.P2.Y * GridStep + (OriginY * GridStep);
      //}

      Sdl->DrawLine(startFrameX, startFrameY, endFrameX, endFrameY, color);
    }

  } else if (ActiveCamera.second == 1) {
    RGB color = RGB(0, 0, 0);

    for (auto& line : Lines) {
      Point3D p1 = line.P1;
      Point3D p2 = line.P2;

      Matrix3D pm = Matrix3D::GetProjectionMatrix(1, 20, 60);

      p1 = p1 * pm;
      p2 = p2 * pm;

      p1.X = (Sdl->Width / 2) + ((p1.X / p1.W) * (Sdl->Width / p1.W));
      p1.Y = (Sdl->Height / 2) + ((p1.Y / p1.W) * (Sdl->Height / p1.W));

      p2.X = (Sdl->Width / 2) + ((p2.X / p2.W) * (Sdl->Width / p2.W));
      p2.Y = (Sdl->Height / 2) + ((p2.Y / p2.W) * (Sdl->Height / p2.W));

      double startFrameX = p1.X + 0;
      double startFrameY = p1.Y + 0;
      double endFrameX = p2.X + 0;
      double endFrameY = p2.Y + 0;

      Sdl->DrawLine(startFrameX, startFrameY, endFrameX, endFrameY, color);
    }
  }
}

void rendererPerspective::BeforeEach() {
  DrawGrid();
  DrawLines();
}

void rendererPerspective::OnKey(int event, int key) {
  std::cout << "key press\n";

  if (event == SDL_KEYUP && key == SDL_SCANCODE_Z) {
    Scale(2, 2, 2);
    std::cout << "Scale up\n";
  }
  if (event == SDL_KEYUP && key == SDL_SCANCODE_X) {
    Scale(0.5, 0.5, 0.5);
    std::cout << "Scale down\n";
  }

  if (event == SDL_KEYUP && key == SDL_SCANCODE_RIGHT) {
    Move(1, 0, 0);
    std::cout << "Move +x\n";
  }
  if (event == SDL_KEYUP && key == SDL_SCANCODE_LEFT) {
    Move(-1, 0, 0);
    std::cout << "Move -x\n";
  }

  if (event == SDL_KEYUP && key == SDL_SCANCODE_UP) {
    Move(0, 0, 1);
    std::cout << "Move +z\n";
  }
  if (event == SDL_KEYUP && key == SDL_SCANCODE_DOWN) {
    Move(0, 0, -1);
    std::cout << "Move -z\n";
  }

  if (event == SDL_KEYUP && key == SDL_SCANCODE_PAGEUP) {
    Move(0, 1, 0);
    std::cout << "Move +y\n";
  }
  if (event == SDL_KEYUP && key == SDL_SCANCODE_PAGEDOWN) {
    Move(0, -1, 0);
    std::cout << "Move -y\n";
  }

  if (event == SDL_KEYDOWN && key == SDL_SCANCODE_A) {
    Rotate(1);
    std::cout << "Rotate +x\n";
  }
  if (event == SDL_KEYDOWN && key == SDL_SCANCODE_D) {
    Rotate(-1);
    std::cout << "Rotate -x\n";
  }

  if (event == SDL_KEYDOWN && key == SDL_SCANCODE_W) {
    Rotate(2);
    std::cout << "Rotate +y\n";
  }
  if (event == SDL_KEYDOWN && key == SDL_SCANCODE_S) {
    Rotate(-2);
    std::cout << "Rotate -y\n";
  }

  if (event == SDL_KEYDOWN && key == SDL_SCANCODE_Q) {
    Rotate(3);
    std::cout << "Rotate +z\n";
  }
  if (event == SDL_KEYDOWN && key == SDL_SCANCODE_E) {
    Rotate(-3);
    std::cout << "Rotate -z\n";
  }

  if (event == SDL_KEYDOWN && key == SDL_SCANCODE_R) {
    Rotate(1);
    Rotate(2);
    Rotate(3);
    std::cout << "Rotate all axis\n";
  }
}

void rendererPerspective::Scale(const double x, const double y,
                                const double z) {
  Point3D localOrigin = Lines.at(0).P1;

  Matrix3D tm1 = Matrix3D::GetTranslationMatrix(
      (-localOrigin.X) - 1, (-localOrigin.Y) - 1, (-localOrigin.Z) - 1);
  Matrix3D tm2 = Matrix3D::GetTranslationMatrix(
      localOrigin.X + 1, localOrigin.Y + 1, localOrigin.Z + 1);
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
  Point3D localOrigin = {2 - 3, 2 - 3, 2 - 15};

  Matrix3D tm1 = Matrix3D::GetTranslationMatrix(
      -(localOrigin.X + 1), -(localOrigin.Y + 1), -(localOrigin.Z + 1));
  Matrix3D tm2 = Matrix3D::GetTranslationMatrix(
      localOrigin.X + 1, localOrigin.Y + 1, localOrigin.Z + 1);
  Matrix3D rm = Matrix3D::GetRotationMatrix(abs(dir), (dir > 0 ? 1 : -1));
  Matrix3D cm = tm2 * rm * tm1;

  for (auto& line : Lines) {
    line.P1 = line.P1 * cm;
    line.P2 = line.P2 * cm;
  }
}
