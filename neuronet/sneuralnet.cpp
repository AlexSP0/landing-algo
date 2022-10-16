#include "sneuralnet.h"
#include "nlink.h"

#include <math.h>

namespace neuro
{
SNeuralNet::SNeuralNet(
    int numInputs, int numOutputs, int numNeuronsByFirstLayer, int hiddenLayers, int hiddenNeurons)
    : m_NumInputs(numInputs)
    , m_NumOutputs(numOutputs)
    , m_NumNeuronsByFirstLayer(numNeuronsByFirstLayer)
    , m_NumHiddenLayers(hiddenLayers)
    , m_NeuronsByHiddenLayers(hiddenNeurons)
{
    createFirstLayer();

    createHiddenLayers();

    createLastLayer();
}

std::vector<double> SNeuralNet::getAllWeights() const
{
    std::vector<double> result;

    if (m_Links.size() == 0)
    {
        return result;
    }

    for (size_t i = 0; i < m_Links.size(); i++)
    {
        result.push_back(m_Links[i].weight);
    }

    return result;
}

void SNeuralNet::putWeights(std::vector<double> &weights)
{
    if (weights.size() != m_Links.size())
    {
        return;
    }

    for (size_t i = 0; i < m_Links.size(); i++)
    {
        m_Links[i].weight = weights[i];
    }
}

std::vector<double> SNeuralNet::Update(std::vector<double> &inputs)
{
    std::vector<double> outputs;

    if (inputs.size() != m_NumInputs)
    {
        return outputs;
    }

    for (size_t i = 0; i < m_layers.size(); i++)
    {
        for (size_t j = 0; j < m_layers[i].m_neurons.size(); j++)
        {
            if (i == 0)
            {
                std::vector<NLink> incomingLinks;
                for (size_t k = 0; k < m_Links.size(); k++)
                {
                    if (m_Links[k].incoming == &m_layers[i].m_neurons[j])
                    {
                        incomingLinks.push_back(m_Links[k]);
                    }
                }

                for (size_t l = 0; l < inputs.size(); l++)
                {
                    m_layers[i].m_neurons[j].m_sumActivation += inputs[l] * incomingLinks[l].weight;
                }

                m_layers[i].m_neurons[j].m_output = sigmoid(
                    m_layers[i].m_neurons[j].m_sumActivation);
            }
            else
            {
                for (size_t k = 0; k < m_Links.size(); k++)
                {
                    if (m_Links[k].incoming == &m_layers[i].m_neurons[j])
                    {
                        m_layers[i].m_neurons[j].m_sumActivation += (m_Links[k].outcoming->m_output
                                                                     * m_Links[k].weight);
                    }
                }

                m_layers[i].m_neurons[j].m_output = sigmoid(
                    m_layers[i].m_neurons[j].m_sumActivation);
            }
        }
    }

    for (size_t o = 0; o < m_layers[m_layers.size() - 1].m_neurons.size(); o++)
    {
        outputs.push_back(m_layers[m_layers.size() - 1].m_neurons[o].m_output);
    }

    return outputs;
}

double SNeuralNet::sigmoid(double activation)
{
    return 1 / (1 + pow(2.7183, (-1 * activation) / 1));
}

void SNeuralNet::createFirstLayer()
{
    SNeuronLayer *firstLayer = new SNeuronLayer(m_NumInputs);

    for (size_t i = 0; i < m_NumNeuronsByFirstLayer; i++)
    {
        SNeuron *newNeuron = new SNeuron(m_NumInputs, CURVATURE);

        newNeuron->type = input_neuron;

        firstLayer->m_neurons.push_back(*newNeuron);
    }

    m_layers.push_back(*firstLayer);

    //Incoming links from beginning values to net
    for (size_t j = 0; j < m_layers[0].m_neurons.size(); j++)
    {
        for (size_t k = 0; k < m_NumInputs; k++)
        {
            NLink *newLink = new NLink;

            newLink->incoming = &m_layers[0].m_neurons[j];

            newLink->outcoming = nullptr;

            m_Links.push_back(*newLink);
        }
    }
}

void SNeuralNet::createHiddenLayers()
{
    for (size_t i = 1; i <= m_NumHiddenLayers; i++)
    {
        SNeuronLayer *currentLayer = new SNeuronLayer(m_layers[i - 1].m_neurons.size());

        for (size_t j = 0; j < m_NeuronsByHiddenLayers; j++)
        {
            SNeuron *newNeuron = new SNeuron(m_layers[i - 1].m_neurons.size(), CURVATURE);

            newNeuron->type = hidden_neuron;

            currentLayer->m_neurons.push_back(*newNeuron);
        }

        m_layers.push_back(*currentLayer);

        //Create links to previous layer
        for (size_t j = 0; j < m_layers[m_layers.size() - 1].m_neurons.size(); j++)
        {
            for (size_t k = 0; k < m_layers[m_layers.size() - 2].m_neurons.size(); k++)
            {
                NLink *newLink = new NLink();

                newLink->incoming = &m_layers[m_layers.size() - 1].m_neurons[j];

                newLink->outcoming = &m_layers[m_layers.size() - 2].m_neurons[k];

                m_Links.push_back(*newLink);
            }
        }
    }
}

void SNeuralNet::createLastLayer()
{
    SNeuronLayer *lastLayer = new SNeuronLayer(m_NeuronsByHiddenLayers);

    for (size_t i = 0; i < m_NumOutputs; i++)
    {
        SNeuron *newNeuron = new SNeuron(m_NeuronsByHiddenLayers, CURVATURE);

        newNeuron->type = output_neuron;

        lastLayer->m_neurons.push_back(*newNeuron);
    }

    m_layers.push_back(*lastLayer);

    //Create link to previous layer
    for (size_t j = 0; j < m_layers[m_layers.size() - 1].m_neurons.size(); j++)
    {
        for (size_t k = 0; k < m_layers[m_layers.size() - 2].m_neurons.size(); k++)
        {
            NLink *newLink = new NLink();

            newLink->incoming = &m_layers[m_layers.size() - 1].m_neurons[j];

            newLink->outcoming = &m_layers[m_layers.size() - 2].m_neurons[k];

            m_Links.push_back(*newLink);
        }
    }
}

} // namespace neuro
