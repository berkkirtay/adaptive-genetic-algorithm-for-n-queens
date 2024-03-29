// Copyright (c) 2022 Berk Kirtay

#include "Chromosome.h"

Chromosome::Chromosome(int size)
{
    this->size = size;
    genes.resize(size, 0);
}

void Chromosome::generateRandomly()
{
    std::vector<int> sampledGenes;
    for (auto i = 0; i < size; i++)
    {
        sampledGenes.push_back(i);
    }

    for (auto i = 0; i < size; i++)
    {
        if (sampledGenes.size() == 1)
        {
            genes[i] = sampledGenes[0];
        }
        else
        {
            auto random = UniformDistributionGenerator::instance()
                              ->generate(sampledGenes.size() - 1);
            genes[i] = sampledGenes[random];
            sampledGenes.erase(sampledGenes.begin() + random);
        }
    }
}

void Chromosome::copy(std::shared_ptr<Chromosome> chromosome)
{
    for (auto i = 0; i < chromosome->size; i++)
    {
        genes[i] = chromosome->genes[i];
    }
    index = chromosome->index;
    fitnessScore = chromosome->fitnessScore;
}

void Chromosome::copyGenes(std::vector<int> genes)
{
    this->genes = genes;
    calculateFitness();
}

void Chromosome::calculateFitness()
{
    fitnessScore = FitnessChecker::instance()->calculateFitnessFunction(genes);
}

bool Chromosome::compare(
    const std::shared_ptr<Chromosome> a,
    const std::shared_ptr<Chromosome> b)
{
    return a->fitnessScore > b->fitnessScore;
}
