#pragma once
#include "UniformDistributionGenerator.h"
#include "Chromosome.h"
#include <memory>

class Mutation
{
private:
    int chromosomeSize = 0;
    double mutationPressure = 0;

public:
    Mutation(
        int chromosomeSize,
        double mutationPressure);

    void mutate(
        std::vector<std::shared_ptr<Chromosome>> &chromosomes,
        double populationVariance);
};
