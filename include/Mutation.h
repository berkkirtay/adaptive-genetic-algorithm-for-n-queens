#pragma once
#include "UniformDistributionGenerator.h"
#include "Chromosome.h"

class Mutation
{
private:
    UniformDistributionGenerator uniformDistGenerator;

public:
    void mutate(std::vector<Chromosome *> &chromosomes, double populationVariance);
};
