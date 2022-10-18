#include "genealgo.h"
#include "constants.h"

#include "QRandomGenerator"

#include <math.h>

GeneAlgo::GeneAlgo() {}

void GeneAlgo::mutate(std::vector<double> &genome)
{
    double random = QRandomGenerator::global()->generateDouble();
    if (random > MUTATION_RATE)
    {
        return;
    }

    double sign = QRandomGenerator::global()->generateDouble();

    int numberOfWeight = QRandomGenerator::global()->bounded(0, genome.size());

    double delta = MUTATION_DELTA;

    if (sign < 0.5)
    {
        delta = MUTATION_DELTA * (-1);
    }

    genome[numberOfWeight] = genome[numberOfWeight] + delta;
}

void GeneAlgo::crossover(std::vector<double> &father,
                         std::vector<double> &mother,
                         std::vector<double> &baby1,
                         std::vector<double> &baby2)
{
    baby1.clear();
    baby2.clear();

    int crossoverPosition = QRandomGenerator::global()->bounded(0, father.size());

    for (size_t i = 0; i < crossoverPosition; i++)
    {
        baby1.push_back(father[i]);
        baby2.push_back(mother[i]);
    }

    for (size_t j = crossoverPosition; j < father.size(); j++)
    {
        baby1.push_back(mother[j]);
        baby2.push_back(father[j]);
    }
}

std::vector<double> GeneAlgo::selection()
{
    std::vector<double> m;
    return m;
}

int GeneAlgo::rouletteWheelSelection(std::vector<Genome> &genomes, double tFitness)
{
    double total = 0;

    double slice = QRandomGenerator::global()->bounded(0, tFitness);

    int selectedGenome = 0;

    for (size_t i = 0; i < genomes.size(); i++)
    {
        total += genomes[i].m_fitness;

        if (total > slice)
        {
            selectedGenome = i;
        }
    }

    return selectedGenome;
}

double GeneAlgo::calculateFitness(
    double xc, double yc, double vs, double hs, int xbl, int xel, int hl)
{
    // расстояние до середины посдочной площадки abs(xc-xbl+(xel-xbl))
    // высота до посадки abs(yc - hl)
    double rangeX          = abs(xc - (xbl + ((xel - xbl) / 2)));
    double rangeY          = abs(yc - hl);
    double vertSpeed       = abs(vs - SUCCESS_HORIZONTAL_SPEED);
    double horizontalSpeed = abs(hs - SUCCESS_VERTICAL_SPEED);
    double fitness         = rangeX + rangeY + vertSpeed + horizontalSpeed;

    if (isinf(fitness))
    {
        qWarning("INF!");
    }

    //return QRandomGenerator::global()->bounded(100);
    return fitness;
}
