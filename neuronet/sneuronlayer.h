#ifndef SNEURONLAYER_H
#define SNEURONLAYER_H

#include "sneuron.h"

namespace neuro
{
class SNeuronLayer
{
public:
    int m_numInputs;

    SNeuronLayer(int numInputs);

    std::vector<SNeuron> m_neurons;

    void updateLayer();
};

} // namespace neuro

#endif // SNEURONLAYER_H
