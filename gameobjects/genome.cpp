#include "genome.h"

Genome::Genome()
    : m_fitness(0)
{}

Genome::Genome(std::vector<double> w, double fit)
    : m_fitness(fit)
{
    for (size_t i = 0; i < w.size(); i++)
    {
        vec_Weights.push_back(w[i]);
    }
}

Genome::Genome(const Genome &other)
{
    m_fitness = other.m_fitness;

    vec_Weights.clear();

    for (size_t i = 0; i < other.vec_Weights.size(); i++)
    {
        vec_Weights.push_back(other.vec_Weights[i]);
    }
}

Genome::Genome(Genome &&other)
{
    m_fitness = other.m_fitness;

    vec_Weights.clear();

    for (size_t i = 0; i < other.vec_Weights.size(); i++)
    {
        vec_Weights.push_back(other.vec_Weights[i]);
    }
}

Genome &Genome::operator=(const Genome &other)
{
    m_fitness = other.m_fitness;

    vec_Weights.clear();

    for (size_t i = 0; i < other.vec_Weights.size(); i++)
    {
        vec_Weights.push_back(other.vec_Weights[i]);
    }

    return *this;
}

Genome &Genome::operator=(Genome &&other)
{
    m_fitness = other.m_fitness;

    vec_Weights.clear();

    for (size_t i = 0; i < other.vec_Weights.size(); i++)
    {
        vec_Weights.push_back(other.vec_Weights[i]);
    }

    return *this;
}

bool Genome::operator<(const Genome &r)
{
    return (m_fitness < r.m_fitness);
}
