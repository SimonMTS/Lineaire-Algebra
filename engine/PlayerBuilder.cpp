#include "PlayerBuilder.hpp"

Structure PlayerBuilder::GetPlayer() {
  Structure s;
  {
    {
      Component o;

      cVector p1(-2, -2, -20);
      cVector p2(-2, 2, -20);
      cVector p3(2, -2, -20);
      cVector p4(2, 2, -20);

      cVector p5(-2, -2, 20);
      cVector p6(-2, 10, 20);
      cVector p7(2, -2, 20);
      cVector p8(2, 10, 20);

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

      s.AddComponent(o);
    }

    {
      Component o;

      cVector p1(-6, -2, -2);
      cVector p2(-6, 10, -2);
      cVector p3(6, -2, -2);
      cVector p4(6, 10, -2);

      cVector p5(-6, -2, 2);
      cVector p6(-6, 10, 2);
      cVector p7(6, -2, 2);
      cVector p8(6, 10, 2);

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

      o.Pos = {0, 0, 22};
      s.AddComponent(o);
    }

    {
      Component o;

      cVector p1(-2, -2, -2);
      cVector p2(-2, 2, -2);
      cVector p3(2, -2, -2);
      cVector p4(2, 2, -2);

      cVector p5(-2, -2, 2);
      cVector p6(-2, 2, 2);
      cVector p7(2, -2, 2);
      cVector p8(2, 2, 2);

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

      o.Pos = {4, 0, -15};
      s.AddComponent(o);
    }

    {
      Component o;

      cVector p1(-2, -2, -2);
      cVector p2(-2, 2, -2);
      cVector p3(2, -2, -2);
      cVector p4(2, 2, -2);

      cVector p5(-2, -2, 2);
      cVector p6(-2, 2, 2);
      cVector p7(2, -2, 2);
      cVector p8(2, 2, 2);

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

      o.Pos = {-4, 0, -15};
      s.AddComponent(o);
    }

    {
      Component o;

      cVector p1(-4, -4, -10);
      cVector p2(-4, 4, -10);
      cVector p3(4, -4, -10);
      cVector p4(4, 4, -10);

      cVector p5(-4, -4, 10);
      cVector p6(-4, 4, 10);
      cVector p7(4, -4, 10);
      cVector p8(4, 4, 10);

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

      o.Pos = {10, 0, -15};
      s.AddComponent(o);
    }

    {
      Component o;

      cVector p1(-4, -4, -10);
      cVector p2(-4, 4, -10);
      cVector p3(4, -4, -10);
      cVector p4(4, 4, -10);

      cVector p5(-1, -1, 4);
      cVector p6(-1, 1, 4);
      cVector p7(1, -1, 4);
      cVector p8(1, 1, 4);

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

      o.Pos = {10, 0, 5};
      s.AddComponent(o);
    }

    {
      Component o;

      cVector p1(-4, -4, -10);
      cVector p2(-4, 4, -10);
      cVector p3(4, -4, -10);
      cVector p4(4, 4, -10);

      cVector p5(-4, -4, 10);
      cVector p6(-4, 4, 10);
      cVector p7(4, -4, 10);
      cVector p8(4, 4, 10);

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

      o.Pos = {-10, 0, -15};
      s.AddComponent(o);
    }

    {
      Component o;

      cVector p1(-4, -4, -10);
      cVector p2(-4, 4, -10);
      cVector p3(4, -4, -10);
      cVector p4(4, 4, -10);

      cVector p5(-1, -1, 0);
      cVector p6(-1, 1, 0);
      cVector p7(1, -1, 0);
      cVector p8(1, 1, 0);

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

      o.Pos = {-10, 0, 5};
      s.AddComponent(o);
    }
  }

  return s;
}
