#pragma once
#include "UniformDistributionGenerator.h"
#include "Chromosome.h"
#include <memory>

class Recombination
{
private:
    int chromosomeSize = 0;
    int popSelectionSize = 0;
    double selectionPressure = 0;

public:
    Recombination(int chromosomeSize,
                  int popSelectionSize, double selectionPressure);
    std::vector<std::shared_ptr<Chromosome>> breedChildChromosomes(std::vector<std::shared_ptr<Chromosome>> &parents,
                                                                   double populationVariance);
    std::vector<std::shared_ptr<Chromosome>> cutAndCrossfillCrossover(
        std::shared_ptr<Chromosome> firstParent, std::shared_ptr<Chromosome> secondParent);
    std::vector<std::shared_ptr<Chromosome>> uniformCrossover(
        std::shared_ptr<Chromosome> firstParent,
        std::shared_ptr<Chromosome> secondParent);
};
