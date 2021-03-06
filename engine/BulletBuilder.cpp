#include "BulletBuilder.hpp"

Structure BulletBuilder::GetBullet() {
  Structure s;
  {
    Component c;

    // create points
    cVector p1(-2, -2, 0);
    cVector p2(-2, 2, 0);
    cVector p3(2, -2, 0);
    cVector p4(2, 2, 0);

    cVector p5(0, 0, 10);
    cVector p6(0, 0, 10);
    cVector p7(0, 0, 10);
    cVector p8(0, 0, 10);

    // create squares
    Square s1(p2, p4, p1, p3);
    Square s2(p6, p8, p5, p7);

    Square s3(p2, p6, p1, p5);
    Square s4(p4, p8, p3, p7);

    Square s5(p5, p7, p1, p3);
    Square s6(p6, p8, p2, p4);

    // add squares to Component
    c.AddSquare(s1);
    c.AddSquare(s2);
    c.AddSquare(s3);
    c.AddSquare(s4);
    c.AddSquare(s5);
    c.AddSquare(s6);

    // add Component to Structure
    s.AddComponent(c);
  }

  return s;
}
