#include "lander.h"

#include <QStaticText>
#include <QWidget>

Lander::Lander(int wx, int wy, Vector2D startPos, Vector2D landingPadPos)
    : GraphicalObject()
    , mass(10)
    , landingPad(landingPadPos)
    , scalingFactor(2)
    , showJet(false)
    , clientWindowX(wx)
    , clientWindowY(wy)
{
    std::vector<std::vector<double>> lander
        = {{0, 2}, {1, 2}, {1, 1}, {2, 1}, {2, -2}, {-2, -2}, {-2, 1}, {-1, 1}, {-1, 2}};

    for (auto point : lander)
    {
        Point newPoint = Point(point[0], point[1]);
        vertices.push_back(newPoint);
    }

    velocity.x = 0;
    velocity.y = 0;

    posX     = startPos.x;
    posY     = startPos.y;
    scaleX   = 5;
    scaleY   = 5;
    rotation = 0;
}

Lander::~Lander() {}

void Lander::render(QPainter *qp)
{
    draw(qp);
}

void Lander::updateShip(double elapsedTime, ACTIONS action)
{
    //    QString time    = QString::number(elapsedTime);
    //    std::string str = time.toStdString();
    //    qWarning(str.c_str());

    if (checkLandedOrCrash())
    {
        return;
    }

    if (action == ACTIONS::THRUST)
    {
        qWarning("THRUST");
        double shipAcceleration = (THRUST_PER_SECOND * elapsedTime) / mass;
        velocity.x              = velocity.x + shipAcceleration * sin(rotation) * (-1);
        velocity.y              = velocity.y + shipAcceleration * cos(rotation);

        showJet = true;
    }

    if (action == ACTIONS::ROTATE_RIGHT)
    {
        qWarning("LEFT");
        rotation = rotation - ROTATION_PER_SECOND * elapsedTime;
        if (rotation < -3.14)
        {
            rotation = rotation + 3.14 * 2;
        }
    }

    if (action == ACTIONS::ROTATE_LEFT)
    {
        qWarning("RIGHT");
        rotation = rotation + ROTATION_PER_SECOND * elapsedTime;
        if (rotation > 3.14 * 2)
        {
            rotation = rotation - 3.14 * 2;
        }
    }

    if (action == ACTIONS::ZERO)
    {
        qWarning("ZERO");
        posX       = 300;
        posY       = 300;
        rotation   = 0.00;
        velocity.x = 0;
        velocity.y = 0;
    }

    velocity.y = velocity.y + GRAVITY * elapsedTime;

    posX = posX + velocity.x * elapsedTime * SCALING_FACTOR;
    posY = posY + velocity.y * elapsedTime * SCALING_FACTOR;

    if (posX > clientWindowX)
    {
        posX = 0;
    }

    if (posX < 0)
    {
        posX = clientWindowX;
    }

    calculateTransVertices();
}

bool Lander::checkLandedOrCrash()
{
    return false;
}
