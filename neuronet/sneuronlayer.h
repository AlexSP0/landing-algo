#ifndef SNEURONLAYER_H
#define SNEURONLAYER_H

#include "sneuron.h"

class SNeuronLayer
{
public:
    SNeuronLayer();

    std::vector<SNeuron> m_neurons;
};

#endif // SNEURONLAYER_H
