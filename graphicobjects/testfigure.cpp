#include "testfigure.h"

TestFigure::TestFigure()
{
    Point z1(-3, 2);
    Point z2(1, 2);
    Point z3(1, 1);
    Point z4(3, 1);
    Point z5(3, -1);
    Point z6(-3, -1);
    vertices.push_back(z1);
    vertices.push_back(z2);
    vertices.push_back(z3);
    vertices.push_back(z4);
    vertices.push_back(z5);
    vertices.push_back(z6);
}
