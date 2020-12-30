#include "RenderEngine.h"
#include "Renderer2D.h"
#include "Renderer3D.h"
#include "rendererPerspective.h"

void addSquare(Renderer& r);
void addSquareOffset(Renderer& r, int offsetZ);
void addPyramid(Renderer& r);

int main() {
  int v = 5;
  // std::cin >> v;

  if (v == 0) {
    // 2D Week 1
    Vector2D a(4, 3);
    Vector2D b(2, -4);
    Vector2D c = (a + b) * 2;
    Vector2D d = b - a;

    Renderer2D r2d;
    r2d.AddVector(a);
    r2d.AddVector(b);
    r2d.AddVector(c);
    r2d.AddVector(d);
    r2d.Init();
  }

  if (v == 1) {
    // 2D Week 2/3
    Point2D p1(1, 1);
    Point2D p2(1, 3);
    Point2D p3(3, 1);
    Point2D p4(3, 3);
    Line2D l1(p1, p2);
    Line2D l2(p1, p3);
    Line2D l3(p2, p4);
    Line2D l4(p3, p4);

    Matrix2D sm = Matrix2D::GetScalingMatrix(2, 2);
    Matrix2D tm1 = Matrix2D::GetTranslationMatrix(-2, -2);
    Matrix2D tm2 = Matrix2D::GetTranslationMatrix(2, 2);
    Matrix2D rm = Matrix2D::GetRotationMatrix(45);
    Matrix2D cm = tm2 * rm * tm1;

    Point2D mp1 = p1 * cm;
    Point2D mp2 = p2 * cm;
    Point2D mp3 = p3 * cm;
    Point2D mp4 = p4 * cm;
    Line2D ml1(mp1, mp2);
    Line2D ml2(mp1, mp3);
    Line2D ml3(mp2, mp4);
    Line2D ml4(mp3, mp4);

    Renderer2D r2d;
    r2d.AddLine(l1);
    r2d.AddLine(l2);
    r2d.AddLine(l3);
    r2d.AddLine(l4);
    // r2d.AddLine(ml1);
    // r2d.AddLine(ml2);
    // r2d.AddLine(ml3);
    // r2d.AddLine(ml4);
    r2d.Init();
  }

  if (v == 2) {
    // 3D Week 4, alleen axis x/y/z
    Renderer3D r3d;

    addPyramid(r3d);

    r3d.Init();
  }

  if (v == 3) {
    // 3D Week 5
    Renderer3D r3d;

    Point3D p1(2, 4, 0);
    Point3D p2(4, 1, 0);
    Line3D l1(p1, p2);
    r3d.AddLine(l1);

    Point3D p3{0, 0, 0};
    Point3D p4 = p1.OutProduct(p2);
    Line3D l2(p3, p4);
    r3d.AddLine(l2);

    r3d.Init();
  }

  if (v == 4) {
    rendererPerspective rPer;

    addSquare(rPer);
    // addSquareOffset(rPer, 5);

    rPer.AddCamera({0, 0, 0}, 1);

    rPer.Init();
  }

  if (v == 5) {
    RenderEngine rEng;

    rEng.AddCamera({0, 0, 1000}, make_unique<CameraPerspective>());
    rEng.AddCamera({50, 50, 50}, make_unique<Camera2D>());
    
    {
      Structure s;
      {
        {
          Object o;

          Point3D p1(-10, -10, -10);
          Point3D p2(-10, 10, -10);
          Point3D p3(10, -10, -10);
          Point3D p4(10, 10, -10);

          Point3D p5(-10, -10, 10);
          Point3D p6(-10, 10, 10);
          Point3D p7(10, -10, 10);
          Point3D p8(10, 10, 10);

          Square s1(p2, p4, p1, p3);
          Square s2(p6, p8, p5, p7);

          Square s3(p2, p6, p1, p5);
          Square s4(p4, p8, p3, p7);

          Square s5(p5, p7, p1, p3);
          Square s6(p6, p8, p2, p4);

          o.AddSquare(s1);
          o.AddSquare(s2);
          o.AddSquare(s3);
          o.AddSquare(s4);
          o.AddSquare(s5);
          o.AddSquare(s6);

          pair<Point3D, Object> po = {{0, 0, 0}, o};
          s.AddObject(po);
        }

        {
          Object o;

          Point3D p1(-5, -5, -5);
          Point3D p2(-5, 5, -5);
          Point3D p3(5, -5, -5);
          Point3D p4(5, 5, -5);

          Point3D p5(-5, -5, 5);
          Point3D p6(-5, 5, 5);
          Point3D p7(5, -5, 5);
          Point3D p8(5, 5, 5);

          Square s1(p2, p4, p1, p3);
          Square s2(p6, p8, p5, p7);

          Square s3(p2, p6, p1, p5);
          Square s4(p4, p8, p3, p7);

          Square s5(p5, p7, p1, p3);
          Square s6(p6, p8, p2, p4);

          o.AddSquare(s1);
          o.AddSquare(s2);
          o.AddSquare(s3);
          o.AddSquare(s4);
          o.AddSquare(s5);
          o.AddSquare(s6);

          pair<Point3D, Object> po = {{15, 0, 0}, o};
          s.AddObject(po);
        }

        {
          Object o;

          Point3D p1(-5, -5, -5);
          Point3D p2(-5, 5, -5);
          Point3D p3(5, -5, -5);
          Point3D p4(5, 5, -5);

          Point3D p5(-5, -5, 5);
          Point3D p6(-5, 5, 5);
          Point3D p7(5, -5, 5);
          Point3D p8(5, 5, 5);

          Square s1(p2, p4, p1, p3);
          Square s2(p6, p8, p5, p7);

          Square s3(p2, p6, p1, p5);
          Square s4(p4, p8, p3, p7);

          Square s5(p5, p7, p1, p3);
          Square s6(p6, p8, p2, p4);

          o.AddSquare(s1);
          o.AddSquare(s2);
          o.AddSquare(s3);
          o.AddSquare(s4);
          o.AddSquare(s5);
          o.AddSquare(s6);

          pair<Point3D, Object> po = {{-15, 0, 0}, o};
          s.AddObject(po);
        }
      }
      pair<Point3D, Structure> ps = {{0, 0, 90}, s};
      rEng.AddStructure(ps);
    }

    rEng.Init();
  }

  return 0;
}

void addSquare(Renderer& r) {
  int xoff = -3;
  int yoff = -3;
  int zoff = -15;

  Point3D p1(2 + xoff, 2 + yoff, 2 + zoff);
  Point3D p2(2 + xoff, 4 + yoff, 2 + zoff);
  Point3D p3(4 + xoff, 2 + yoff, 2 + zoff);
  Point3D p4(4 + xoff, 4 + yoff, 2 + zoff);

  Point3D p5(2 + xoff, 2 + yoff, 4 + zoff);
  Point3D p6(2 + xoff, 4 + yoff, 4 + zoff);
  Point3D p7(4 + xoff, 2 + yoff, 4 + zoff);
  Point3D p8(4 + xoff, 4 + yoff, 4 + zoff);

  Line3D l1(p1, p2);
  Line3D l2(p1, p3);
  Line3D l3(p4, p2);
  Line3D l4(p4, p3);

  Line3D l5(p5, p6);
  Line3D l6(p5, p7);
  Line3D l7(p8, p6);
  Line3D l8(p8, p7);

  Line3D l9(p1, p5);
  Line3D l10(p2, p6);
  Line3D l11(p3, p7);
  Line3D l12(p4, p8);

  r.AddLine(l1);
  r.AddLine(l2);
  r.AddLine(l3);
  r.AddLine(l4);
  r.AddLine(l5);
  r.AddLine(l6);
  r.AddLine(l7);
  r.AddLine(l8);
  r.AddLine(l9);
  r.AddLine(l10);
  r.AddLine(l11);
  r.AddLine(l12);
}

void addSquareOffset(Renderer& r, int offsetZ) {
  Point3D p1(2, 2, 2 + offsetZ);
  Point3D p2(2, 4, 2 + offsetZ);
  Point3D p3(4, 2, 2 + offsetZ);
  Point3D p4(4, 4, 2 + offsetZ);

  Point3D p5(2, 2, 4 + offsetZ);
  Point3D p6(2, 4, 4 + offsetZ);
  Point3D p7(4, 2, 4 + offsetZ);
  Point3D p8(4, 4, 4 + offsetZ);

  Line3D l1(p1, p2);
  Line3D l2(p1, p3);
  Line3D l3(p4, p2);
  Line3D l4(p4, p3);

  Line3D l5(p5, p6);
  Line3D l6(p5, p7);
  Line3D l7(p8, p6);
  Line3D l8(p8, p7);

  Line3D l9(p1, p5);
  Line3D l10(p2, p6);
  Line3D l11(p3, p7);
  Line3D l12(p4, p8);

  r.AddLine(l1);
  r.AddLine(l2);
  r.AddLine(l3);
  r.AddLine(l4);
  r.AddLine(l5);
  r.AddLine(l6);
  r.AddLine(l7);
  r.AddLine(l8);
  r.AddLine(l9);
  r.AddLine(l10);
  r.AddLine(l11);
  r.AddLine(l12);
}

void addPyramid(Renderer& r) {
  Point3D p1(2, 2, 2);
  Point3D p2(2, 2, 5);
  Point3D p3(5, 2, 2);
  Point3D p4(5, 2, 5);
  Point3D p5(3, 5, 4);

  Line3D l1(p1, p2);
  Line3D l2(p1, p3);
  Line3D l3(p4, p2);
  Line3D l4(p4, p3);

  Line3D l5(p1, p5);
  Line3D l6(p2, p5);
  Line3D l7(p3, p5);
  Line3D l8(p4, p5);

  r.AddLine(l1);
  r.AddLine(l2);
  r.AddLine(l3);
  r.AddLine(l4);
  r.AddLine(l5);
  r.AddLine(l6);
  r.AddLine(l7);
  r.AddLine(l8);
}
