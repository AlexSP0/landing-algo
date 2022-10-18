#ifndef GENEALGO_H
#define GENEALGO_H

#include "genome.h"
#include <vector>

class GeneAlgo
{
public:
    GeneAlgo();

    void mutate(std::vector<double> &genome);

    void crossover(std::vector<double> &farther,
                   std::vector<double> &mother,
                   std::vector<double> &baby1,
                   std::vector<double> &baby2);

    std::vector<double> selection();

    int rouletteWheelSelection(std::vector<Genome> &genomes, double tFitness);

    double calculateFitness(double xc, double yc, double vh, double vv, int xbl, int xel, int hl);
};

#endif // GENEALGO_H
