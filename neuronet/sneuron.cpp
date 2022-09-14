#include "sneuron.h"

#include <QRandomGenerator>

SNeuron::SNeuron(int numInputs)
{
    for (size_t i = 0; i < numInputs; i++)
    {
        double value = QRandomGenerator::global()->generateDouble();
        double sign  = QRandomGenerator::global()->generateDouble();
        if (sign > 0.5)
        {
            value = value * (-1);
        }
        m_Inputs_Weights.push_back(value);
    }

    //double bias = QRandomGenerator::global()->generateDouble();
    m_Inputs_Weights.push_back(-1); //the bias value
}
