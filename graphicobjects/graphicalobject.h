#ifndef GRAPHICALOBJECT_H
#define GRAPHICALOBJECT_H

#include "point.h"

#include <vector>
#include <QPainter>

class GraphicalObject
{
    struct MatrixEntry
    {
        double x;
        double y;
        double z;
        MatrixEntry(double a = 0.0, double b = 0.0, double c = 0.0)
            : x(a)
            , y(b)
            , z(c)
        {}
    };

public:
    double posX;
    double posY;
    double scaleX;
    double scaleY;
    double rotation;

    std::vector<Point> vertices;

public:
    GraphicalObject();

    void draw(QPainter *);

    void calculateTransVertices();

private:
    std::vector<Point> transVertices;
    std::vector<MatrixEntry> identityMatrix;
    std::vector<MatrixEntry> translationMatrix;
    std::vector<MatrixEntry> scaleMatrix;
    std::vector<MatrixEntry> rotationMatrix;

    void createIdentityMatrix();
    void createTranslationMatrix();
    void createScaleMatrix();
    void createRotationMatrix();

    void multipleMatrix(MatrixEntry &, const MatrixEntry &, const std::vector<MatrixEntry> &);
};

#endif // GRAPHICALOBJECT_H
