#include "lander.h"

#include <QStaticText>
#include <QWidget>

Lander::Lander(int wx, int wy, Vector2D startPos, LandingPad lPad)
    : GraphicalObject()
    , mass(10)
    , scalingFactor(2)
    , showJet(false)
    , clientWindowX(wx)
    , clientWindowY(wy)
    , landingPad(lPad)
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

    netBrain = std::make_unique<neuro::SNeuralNet>(7, 2, 7, 5, 10);

    //netBrain = new neuro::SNeuralNet(7, 2, 7, 5, 10);
}

Lander::~Lander() {}

void Lander::setGenome(Genome *genome)
{
    m_genome = genome;

    netBrain->putWeights(m_genome->vec_Weights);
}

void Lander::render(QPainter *qp)
{
    draw(qp);
}

void Lander::updateShip(double elapsedTime, ACTIONS action)
{
    //    QString time    = QString::number(elapsedTime);
    //    std::string str = time.toStdString();
    //    qWarning(str.c_str());

    if (isLandedOk() || testForImpact())
    {
        return;
    }

    if (action == ACTIONS::THRUST)
    {
        //qWarning("THRUST");
        double shipAcceleration = (THRUST_PER_SECOND * elapsedTime) / mass;
        velocity.x              = velocity.x + shipAcceleration * sin(rotation) * (-1);
        velocity.y              = velocity.y + shipAcceleration * cos(rotation);

        showJet = true;
    }

    if (action == ACTIONS::ROTATE_RIGHT)
    {
        //qWarning("LEFT");
        rotation = rotation - ROTATION_PER_SECOND * elapsedTime;
        if (rotation < -3.14)
        {
            rotation = rotation + 3.14 * 2;
        }
    }

    if (action == ACTIONS::ROTATE_LEFT)
    {
        //qWarning("RIGHT");
        rotation = rotation + ROTATION_PER_SECOND * elapsedTime;
        if (rotation > 3.14 * 2)
        {
            rotation = rotation - 3.14 * 2;
        }
    }

    if (action == ACTIONS::ZERO)
    {
        //qWarning("ZERO");
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
}

void Lander::updateShipQuietly()
{
    std::vector<double> inputs;
    inputs.push_back(posX);
    inputs.push_back(posY);
    inputs.push_back(velocity.x);
    inputs.push_back(velocity.y);
    inputs.push_back(landingPad.xBegin);
    inputs.push_back(landingPad.xEnd);
    inputs.push_back(landingPad.height);

    std::vector<double> outputs = netBrain->Update(inputs);

    double normAction = 1 / outputs[0];

    double normTime = 1 / outputs[1];

    if (normAction < 0.25)
    {
        updateShip(normTime, ACTIONS::ROTATE_LEFT);
    }
    if (normAction > 0.25 && normAction < 0.5)
    {
        updateShip(normTime, ACTIONS::ROTATE_RIGHT);
    }

    if (normAction > 0.5 && normAction < 0.75)
    {
        updateShip(normTime, ACTIONS::THRUST);
    }

    if (normAction > 0.75)
    {
        updateShip(normTime, ACTIONS::THRUST);
    }

    m_genome->m_fitness = algo.calculateFitness(posX,
                                                posY,
                                                velocity.x,
                                                velocity.y,
                                                landingPad.xBegin,
                                                landingPad.xEnd,
                                                landingPad.height);
}

bool Lander::isLandedOk()
{
    if (posX > landingPad.xEnd && posX < landingPad.xBegin)
    {
        return false;
    }

    if (posY > landingPad.height + SUCCESS_HEIGHT && posY < landingPad.height)
    {
        return false;
    }

    if (abs(velocity.x) > SUCCESS_HORIZONTAL_SPEED)
    {
        return false;
    }

    if (abs(velocity.y < SUCCESS_VERTICAL_SPEED))
    {
        return false;
    }

    return true;
}

bool Lander::testForImpact()
{
    if (posY < 0)
    {
        return true;
    }

    if (posX > landingPad.xBegin && posY < landingPad.xEnd && posY == landingPad.height)
    {
        return true;
    }

    return false;
}
