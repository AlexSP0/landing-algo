#include "testfigure.h"

TestFigure::TestFigure()
{
    Point z1(0, 3);
    Point z2(0.5, 1);
    Point z3(3, 1);
    Point z4(1.25, 0);
    Point z5(2, -2);
    Point z6(0, -1);
    Point z7(-2, -2);
    Point z8(-1.25, 0);
    Point z9(-3, 1);
    Point z10(-0.5, 1);
    vertices.push_back(z1);
    vertices.push_back(z2);
    vertices.push_back(z3);
    vertices.push_back(z4);
    vertices.push_back(z5);
    vertices.push_back(z6);
    vertices.push_back(z7);
    vertices.push_back(z8);
    vertices.push_back(z9);
    vertices.push_back(z10);
}
