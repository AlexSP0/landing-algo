#ifndef SNEURON_H
#define SNEURON_H

#include "nlink.h"
#include <vector>

namespace neuro
{
class SNeuron
{
public:
    neuron_type type = none;

    int m_numInputs = 0;

    double m_output = 0; //Output of this neuron

    double m_sumActivation = 0; // Sum of weights x inputs

    double m_activationResponse = 0; //Curvature

    SNeuron(int numInputs, double curvature);

    std::vector<double> m_Inputs_Weights;
};

} // namespace neuro

#endif // SNEURON_H
