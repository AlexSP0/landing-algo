#include "genecontroller.h"
#include "genealgo.h"

#include <QRandomGenerator>

GeneController::GeneController(int size)
    : isBusy(true)
{
    generateFirstGeneration();

    generateNewLanders();
}

void GeneController::trainNext()
{
    if (currentEpoch > TOTAL_EPOCHS)
    {
        currentEpoch = 0;
        isBusy       = false;
        return;
    }

    if (currentGeneration < NUMBER_GENERATION_BY_EPOCH)
    {
        if (currentLander < NUMBER_LANDERS_IN_GENERATION)
        {
            currentLanders[currentLander]->updateShipQuietly();
            currentLander++;
        }
        else
        {
            currentLander = 0;

            GenerationResult result = GenerationResult();

            double totalFit = getTotalFitness();

            saveResults(totalFit);

            breedNewGeneration(NUMBER_LANDERS_IN_GENERATION, totalFit);

            currentGeneration++;
        }
    }
    else
    {
        currentGeneration = 0;

        //        double totalFit = getTotalFitness();

        //        saveResults(totalFit);

        //breedNewGeneration(NUMBER_LANDERS_IN_GENERATION, totalFit);

        currentEpoch++;
    }
}

void GeneController::breedNewGeneration(int size, double tFitness)
{
    GeneAlgo algo = GeneAlgo();

    std::vector<Genome> newGenomes;

    for (size_t i = 0; i < size / 2; i++)
    {
        int dad = algo.rouletteWheelSelection(currentGenomes, tFitness);
        int mom = algo.rouletteWheelSelection(currentGenomes, tFitness);

        Genome baby1 = Genome();
        Genome baby2 = Genome();

        algo.crossover(currentGenomes[dad].vec_Weights,
                       currentGenomes[mom].vec_Weights,
                       baby1.vec_Weights,
                       baby2.vec_Weights);

        algo.mutate(baby1.vec_Weights);
        algo.mutate(baby2.vec_Weights);

        newGenomes.push_back(baby1);
        newGenomes.push_back(baby2);
    }

    currentGenomes.clear();

    for (size_t i = 0; i < newGenomes.size(); i++)
    {
        currentGenomes.push_back(newGenomes[i]);
    }

    generateNewLanders();
}

Genome GeneController::getBestGenome()
{
    double bestFitness      = 0;
    size_t bestFitnessIndex = 0;

    for (size_t i = 0; i < currentLanders.size(); i++)
    {
        if (currentLanders[i].get()->m_genome->m_fitness > bestFitness)
        {
            bestFitness = currentGenomes[i].m_fitness;
        }
    }

    return currentGenomes[bestFitnessIndex];
}

double GeneController::getTotalFitness()
{
    double total = 0;
    for (size_t i = 0; i < currentLanders.size(); i++)
    {
        if (currentLanders[i].get()->m_genome->m_fitness > total)
        {
            total = total + currentLanders[i].get()->m_genome->m_fitness;
        }
    }

    return total;
}

void GeneController::generateFirstGeneration()
{
    for (size_t i = 0; i < NUMBER_LANDERS_IN_GENERATION; i++)
    {
        Genome newGenome = Genome();

        for (size_t j = 0; j < NUMBER_GENES_IN_GENOME; j++)
        {
            double sign = QRandomGenerator::global()->generateDouble();

            double newWeight = QRandomGenerator::global()->generateDouble();

            if (sign < 0.5)
            {
                newWeight = newWeight * (-1);
            }

            newGenome.vec_Weights.push_back(newWeight);
        }

        currentGenomes.push_back(newGenome);
    }
}

void GeneController::generateNewLanders()
{
    currentLanders.clear();

    for (size_t i = 0; i < NUMBER_LANDERS_IN_GENERATION; i++)
    {
        int startXCoordinate = QRandomGenerator::global()->bounded(0, WINDOW_SIZE_X);
        int startYCoordinate = QRandomGenerator::global()->bounded(0, WINDOW_SIZE_Y);

        std::unique_ptr<Lander> newLander
            = std::make_unique<Lander>(WINDOW_SIZE_X,
                                       WINDOW_SIZE_Y,
                                       Vector2D(startXCoordinate, startYCoordinate),
                                       *new LandingPad(LANDING_PAD_X,
                                                       LANDING_PAD_X + LANDING_PAD_WIDTH,
                                                       LANDING_PAD_HEIGHT));
        newLander->setGenome(&currentGenomes[i]);

        currentLanders.push_back(std::move(newLander));
    }
}

void GeneController::saveResults(double totalFitness)
{
    GenerationResult result = GenerationResult();

    result.epoch        = currentEpoch;
    result.generation   = currentGeneration;
    result.bestFitness  = getBestGenome().m_fitness;
    result.totalFitness = totalFitness;

    results.push_back(result);
}
