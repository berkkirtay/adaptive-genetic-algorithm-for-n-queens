#pragma once
#include "UniformDistributionGenerator.h"
#include "Chromosome.h"

class Recombination
{
private:
    UniformDistributionGenerator uniformDistGenerator;
    double selectionPressure = 0;

public:
    Recombination(double selectionPressure);
    std::vector<Chromosome *> breedChildChromosomes(std::vector<Chromosome *> parents,
                                                    double populationVariance);
    std::vector<Chromosome *> cutAndCrossfillCrossover(
        Chromosome *firstParent, Chromosome *secondParent);
    std::vector<Chromosome *> uniformCrossover(
        Chromosome *firstParent,
        Chromosome *secondParent);
};
