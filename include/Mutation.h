#pragma once
#include "UniformDistributionGenerator.h"
#include "Chromosome.h"

class Mutation
{
private:
    double mutationPressure = 0;
    UniformDistributionGenerator uniformDistGenerator;

public:
    Mutation(double mutationPressure);
    void mutate(std::vector<Chromosome *> &chromosomes, double populationVariance);
};
