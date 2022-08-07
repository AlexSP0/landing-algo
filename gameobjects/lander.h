#ifndef LANDER_H
#define LANDER_H

#include "../constants.h"
#include "../graphicobjects/graphicalobject.h"
#include "../graphicobjects/point.h"
#include "../graphicobjects/vector2d.h"

#include <math.h>

class Lander : public GraphicalObject
{
public:
    Lander(int, int, Vector2D, Vector2D);
    ~Lander();

    void render(QPainter *qp);

    void updateShip(double elapsedTime, ACTIONS action);

    Vector2D velocity;

private:
    double mass;

    Vector2D landingPad;

    double scalingFactor;

    bool showJet;

    int clientWindowX;
    int clientWindowY;

    bool isLandedOk();

    bool testForImpact();

    bool checkLandedOrCrash();
};

#endif // LANDER_H
