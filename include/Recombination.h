#pragma once
#include "UniformDistributionGenerator.h"
#include "Chromosome.h"

class Recombination
{
private:
    int chromosomeSize = 0;
    int popSelectionSize = 0;
    double selectionPressure = 0;

public:
    Recombination(int chromosomeSize,
                  int popSelectionSize, double selectionPressure);
    std::vector<Chromosome *> breedChildChromosomes(std::vector<Chromosome *> parents,
                                                    double populationVariance);
    std::vector<Chromosome *> cutAndCrossfillCrossover(
        Chromosome *firstParent, Chromosome *secondParent);
    std::vector<Chromosome *> uniformCrossover(
        Chromosome *firstParent,
        Chromosome *secondParent);
};
