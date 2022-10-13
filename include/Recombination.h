#pragma once
#include "UniformDistributionGenerator.h"
#include "Chromosome.h"

class Recombination
{
private:
    UniformDistributionGenerator uniformDistGenerator;

public:
    std::vector<Chromosome *> breedChildChromosomes(std::vector<Chromosome *> parents);
    std::vector<Chromosome *> cutAndCrossfillCrossover(
        Chromosome *firstParent, Chromosome *secondParent);
    std::vector<Chromosome *> uniformCrossover(
        Chromosome *firstParent,
        Chromosome *secondParent);
};
