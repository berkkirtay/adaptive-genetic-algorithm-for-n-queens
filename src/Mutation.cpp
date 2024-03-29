// Copyright (c) 2022 Berk Kirtay

#include "Mutation.h"

Mutation::Mutation(int chromosomeSize, double mutationPressure)
{
    this->chromosomeSize = chromosomeSize;
    this->mutationPressure = mutationPressure;
}

void Mutation::mutate(
    std::vector<std::shared_ptr<Chromosome>> &chromosomes,
    double populationVariance)
{
    if (populationVariance < mutationPressure)
    {
        for (auto chromosome : chromosomes)
        {
            int firstRandom = UniformDistributionGenerator::instance()
                                  ->generate(chromosomeSize);
            int secondRandom = UniformDistributionGenerator::instance()
                                   ->generate(chromosomeSize);
            int temp = chromosome->genes[firstRandom];
            chromosome->genes[firstRandom] = chromosome->genes[secondRandom];
            chromosome->genes[secondRandom] = temp;
        }
    }
}