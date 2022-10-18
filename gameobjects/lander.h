#ifndef LANDER_H
#define LANDER_H

#include "..//gameobjects/genome.h"
#include "../gameobjects/constants.h"
#include "../graphicobjects/graphicalobject.h"
#include "../graphicobjects/point.h"
#include "../graphicobjects/vector2d.h"
#include "../neuronet/sneuralnet.h"
#include "genealgo.h"

#include <math.h>
#include <memory.h>

namespace neuro
{
class SNeuralNet;
}
class Lander : public GraphicalObject
{
public:
    Lander(int, int, Vector2D, LandingPad);

    ~Lander();

    Vector2D velocity;

    Genome *m_genome;

    LandingPad landingPad;

    std::unique_ptr<neuro::SNeuralNet> netBrain;

public:
    void render(QPainter *qp);

    void updateShip(double elapsedTime, ACTIONS action);

    void updateShipQuietly();

    void setGenome(Genome *genome);

    bool isLandedOk();

    bool testForImpact();

private:
    double mass;

    double scalingFactor;

    bool showJet;

    int clientWindowX;
    int clientWindowY;

    GeneAlgo algo;
};

#endif // LANDER_H
