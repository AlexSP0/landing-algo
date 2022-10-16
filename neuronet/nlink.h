#ifndef NLINK_H
#define NLINK_H

#include "sneuron.h"

namespace neuro
{
class SNeuron;

struct NLink
{
    SNeuron *incoming;
    SNeuron *outcoming;
    double weight;

    NLink()
        : weight(0)
    {}
    NLink(double w)
        : weight(w)
    {}
};

enum neuron_type
{
    input_neuron,
    hidden_neuron,
    output_neuron,
    none
};

const double CURVATURE = 1;

} // namespace neuro

#endif // NLINK_H
