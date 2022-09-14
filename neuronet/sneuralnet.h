#ifndef SNEURALNET_H
#define SNEURALNET_H

#include "sneuronlayer.h"

#include <vector>

class SNeuralNet
{
public:
    SNeuralNet(int numInputs, int numOutputs, int hiddenLayers, int hiddenNeurons);

    std::vector<double> getAllWeights() const;

    void putWeights(std::vector<double> &wights);

    std::vector<double> Update(std::vector<double> &inputs);

private:
    int m_NumInputs;

    int m_NumOutputs;

    int m_NumHiddenLayers;

    int m_NeuronsByHiddenLayers;

    std::vector<SNeuronLayer> m_layers;

private:
    void CreateNet();

    inline double sigmoid(double activation, double response);
};

#endif // SNEURALNET_H
