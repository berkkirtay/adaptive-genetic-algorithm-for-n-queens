// Copyright (c) 2022 Berk Kirtay

#include "Recombination.h"

Recombination::Recombination(
    int chromosomeSize,
    int popSelectionSize)
{
    this->chromosomeSize = chromosomeSize;
    this->popSelectionSize = popSelectionSize;
}

std::vector<std::shared_ptr<Chromosome>> Recombination::breedChildChromosomes(
    std::vector<std::shared_ptr<Chromosome>> &parents)
{
    std::vector<std::shared_ptr<Chromosome>> children;
    auto l = 0, r = popSelectionSize - 1;
    while (l < r)
    {
        auto breedChildren = cutAndCrossfillCrossover(parents[l], parents[r]);
        children.push_back(breedChildren[0]);
        children.push_back(breedChildren[1]);
        l++;
        r--;
    }

    return children;
}

std::vector<std::shared_ptr<Chromosome>> Recombination::cutAndCrossfillCrossover(
    std::shared_ptr<Chromosome> firstParent,
    std::shared_ptr<Chromosome> secondParent)
{
    auto firstChildren = std::make_shared<Chromosome>(Chromosome(chromosomeSize));
    auto secondChildren = std::make_shared<Chromosome>(Chromosome(chromosomeSize));

    auto random = UniformDistributionGenerator::instance()->generate(chromosomeSize - 1);

    for (auto i = 0; i < random; i++)
    {
        firstChildren->genes[i] = firstParent->genes[i];
        secondChildren->genes[i] = secondParent->genes[i];
    }

    for (auto i = random; i < chromosomeSize; i++)
    {
        firstChildren->genes[i] = secondParent->genes[i];
        secondChildren->genes[i] = firstParent->genes[i];
    }

    return {firstChildren, secondChildren};
}

std::vector<std::shared_ptr<Chromosome>> Recombination::uniformCrossover(
    std::shared_ptr<Chromosome> firstParent,
    std::shared_ptr<Chromosome> secondParent)
{
    auto firstChildren = std::make_shared<Chromosome>(Chromosome(chromosomeSize));
    auto secondChildren = std::make_shared<Chromosome>(Chromosome(chromosomeSize));

    for (auto i = 0; i < chromosomeSize; i++)
    {
        if (i % 2 == 0)
        {
            firstChildren->genes[i] = firstParent->genes[i];
            secondChildren->genes[i] = secondParent->genes[i];
        }
        else
        {
            firstChildren->genes[i] = secondParent->genes[i];
            secondChildren->genes[i] = firstParent->genes[i];
        }
    }

    return {firstChildren, secondChildren};
}