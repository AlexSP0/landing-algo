#ifndef GENOME_H
#define GENOME_H

#include <vector>

class Genome
{
public:
    double m_fitness = 0;

    std::vector<double> vec_Weights;

    Genome();

    Genome(std::vector<double> w, double fit);

    Genome(const Genome &other); //copy ctor

    Genome(Genome &&other); //move ctor

    Genome &operator=(const Genome &other);

    Genome &operator=(Genome &&other);

    bool operator<(const Genome &r);
};

#endif // GENOME_H
