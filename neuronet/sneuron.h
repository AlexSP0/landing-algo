#ifndef SNEURON_H
#define SNEURON_H

#include <vector>

class SNeuron
{
public:
    SNeuron(int numInputs);

    std::vector<double> m_Inputs_Weights;
};

#endif // SNEURON_H
