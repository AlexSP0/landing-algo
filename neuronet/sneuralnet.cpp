#include "sneuralnet.h"

#include <math.h>

SNeuralNet::SNeuralNet(int numInputs, int numOutputs, int hiddenLayers, int hiddenNeurons)
    : m_NumInputs(numInputs)
    , m_NumOutputs(numOutputs)
    , m_NumHiddenLayers(hiddenLayers)
    , m_NeuronsByHiddenLayers(hiddenNeurons)
{
    CreateNet();
}

std::vector<double> SNeuralNet::getAllWeights() const {}

void SNeuralNet::putWeights(std::vector<double> &wights) {}

std::vector<double> SNeuralNet::Update(std::vector<double> &inputs) {}

void SNeuralNet::CreateNet()
{
    if (m_NumHiddenLayers > 0)
    {
        for (size_t i = 0; i < m_NumHiddenLayers; i++)
        {
            SNeuronLayer currentLayer;

            for (size_t j = 0; j < m_NeuronsByHiddenLayers; j++)
            {
                SNeuron currentNeuron(m_NumInputs);

                currentLayer.m_neurons.push_back(currentNeuron);
            }
        }

        SNeuronLayer lastLayer;

        for (size_t i = 0; i < m_NumOutputs; i++)
        {
            SNeuron currentNeuron(m_NeuronsByHiddenLayers);
            lastLayer.m_neurons.push_back(currentNeuron);
        }

        m_layers.push_back(lastLayer);
    }
}

double SNeuralNet::sigmoid(double activation, double response)
{
    return 1 / (1 + pow(2.7183, (-1 * activation) / 1));
}
