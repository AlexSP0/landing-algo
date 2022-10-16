#ifndef SNEURALNET_H
#define SNEURALNET_H

#include "sneuronlayer.h"

#include <vector>

namespace neuro
{
class SNeuralNet
{
public:
    SNeuralNet(int numInputs,
               int numOutputs,
               int numNeuronsByFirstLayer,
               int hiddenLayers,
               int hiddenNeurons);

    std::vector<double> getAllWeights() const;

    void putWeights(std::vector<double> &wights);

    std::vector<double> Update(std::vector<double> &inputs);

private:
    int m_NumInputs;

    int m_NumOutputs;

    int m_NumHiddenLayers;

    int m_NeuronsByHiddenLayers;

    int m_NumNeuronsByFirstLayer;

    std::vector<SNeuronLayer> m_layers;

    std::vector<NLink> m_Links;

private:
    inline double sigmoid(double activation);

    void createFirstLayer();

    void createHiddenLayers();

    void createLastLayer();
};

} // namespace neuro

#endif // SNEURALNET_H
