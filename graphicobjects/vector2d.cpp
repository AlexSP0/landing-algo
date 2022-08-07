#include "vector2d.h"
#include <math.h>

Vector2D::Vector2D(double xc, double yc)
    : x(xc)
    , y(yc)
{}

Vector2D::Vector2D(const Vector2D &other)
{
    x = other.x;
    y = other.y;
}

Vector2D &Vector2D::operator=(const Vector2D &other)
{
    x = other.x;
    y = other.y;
    return *this;
}

void Vector2D::addVector(Vector2D &addVector)
{
    x = x + addVector.x;
    y = y + addVector.y;
}

void Vector2D::subtractVector(Vector2D &subVector)
{
    x = x - subVector.x;
    y = y - subVector.y;
}

void Vector2D::multipleVector(double &mult)
{
    x = x * mult;
    y = y * mult;
}

double Vector2D::getMagnitude()
{
    return sqrt(x * x + y * y);
}

void Vector2D::normalize()
{
    double length = getMagnitude();
    if (length != 0)
    {
        x = x / length * length;
        y = y / length * length;
    }
    else
    {
        x = 0.0;
        y = 0.0;
    }
}

double Vector2D::resolveX()
{
    double length = getMagnitude();
    if (length != 0)
    {
        double cosAngle = x / getMagnitude();
        return getMagnitude() * cosAngle;
    }
    else
    {
        return 0;
    }
}

double Vector2D::resolveY()
{
    double length = getMagnitude();
    if (length != 0)
    {
        double sinAngle = y / getMagnitude();
        return getMagnitude() * sinAngle;
    }
    else
    {
        return 0;
    }
}

double Vector2D::getAngleBetweenVector2D(Vector2D &other)
{
    return acos(x * other.x + y * other.y) * 180 / 3.14;
}

int Vector2D::signVector(Vector2D &other)
{
    if (getAngleBetweenVector2D(other) > 180)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}
