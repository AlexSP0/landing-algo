#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:
    Vector2D(double x = 0.0, double y = 0.0);

    Vector2D(const Vector2D &other); //copy ctor
    Vector2D(Vector2D &&);           //move ctor

    Vector2D &operator=(const Vector2D &other); //copy assignment
    Vector2D &operator=(Vector2D &&other);      //move assignment

    void addVector(Vector2D &);
    void subtractVector(Vector2D &);

    void multipleVector(double &);

    double getMagnitude();

    void normalize();

    double resolveX();
    double resolveY();

    double getAngleBetweenVector2D(Vector2D &);

    int signVector(Vector2D &);

    double x;
    double y;
};

#endif // VECTOR2D_H
