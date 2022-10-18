#ifndef GENECONTROLLER_H
#define GENECONTROLLER_H

#include "genome.h"
#include "lander.h"

#include <vector>

struct GenerationResult
{
    int epoch;
    int generation;
    double bestFitness;
    double totalFitness;

    GenerationResult()
        : epoch(0)
        , generation(0)
        , bestFitness(0)
        , totalFitness(0)
    {}
};

class GeneController
{
public:
    GeneController(int size);

    int currentLander     = 0;
    int currentEpoch      = 0;
    int currentGeneration = 0;

    std::vector<Genome> currentGenomes;
    std::vector<std::unique_ptr<Lander>> currentLanders;
    std::vector<GenerationResult> results;

    bool isBusy;

    void breedNewGeneration(int size, double tFitness);

    Genome getBestGenome();

    double getTotalFitness();

    void trainNext();

private:
    void generateFirstGeneration();

    void generateNewLanders();

    void saveResults(double totalFitness);
};

#endif // GENECONTROLLER_H
