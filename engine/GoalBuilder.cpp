#include "GoalBuilder.hpp"

Structure GoalBuilder::GetGoal() {
  Structure s;
  {
    Component c;

    // create points
    cVector p1(-10, -10, -10);
    cVector p2(-10, 10, -10);
    cVector p3(10, -10, -10);
    cVector p4(10, 10, -10);

    cVector p5(-10, -10, 10);
    cVector p6(-10, 10, 10);
    cVector p7(10, -10, 10);
    cVector p8(10, 10, 10);

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

  {
    Component c;

    // create points
    cVector p1(-5, 10, -5);
    cVector p2(-5, 15, -5);
    cVector p3(5, 10, -5);
    cVector p4(5, 15, -5);

    cVector p5(-5, 10, 5);
    cVector p6(-5, 15, 5);
    cVector p7(5, 10, 5);
    cVector p8(5, 15, 5);

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

  {
    Component c;

    // create points
    cVector p1(-5, -10, -5);
    cVector p2(-5, -15, -5);
    cVector p3(5, -10, -5);
    cVector p4(5, -15, -5);

    cVector p5(-5, -10, 5);
    cVector p6(-5, -15, 5);
    cVector p7(5, -10, 5);
    cVector p8(5, -15, 5);

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
