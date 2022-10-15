#pragma once
#include "UniformDistributionGenerator.h"
#include "Chromosome.h"

class Mutation
{
private:
    int chromosomeSize = 0;
    double mutationPressure = 0;

public:
    Mutation(int chromosomeSize,
             double mutationPressure);
    void mutate(std::vector<Chromosome *> &chromosomes, double populationVariance);
};
