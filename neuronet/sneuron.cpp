#include "sneuron.h"

#include <QRandomGenerator>

namespace neuro
{
SNeuron::SNeuron(int numInputs, double curvature)
    : m_numInputs(numInputs)
    , m_activationResponse(curvature)
{}

} // namespace neuro
