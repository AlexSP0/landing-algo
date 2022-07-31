#ifndef POINT_H
#define POINT_H

struct Point
{
    double x;
    double y;

    Point(double a = 0.0, double b = 0.0)
        : x(a)
        , y(b)
    {}
};

#endif //POINT_H
