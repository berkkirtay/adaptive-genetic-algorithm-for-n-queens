#include "Recombination.h"

Recombination::Recombination(int chromosomeSize,
                             int popSelectionSize,
                             double selectionPressure)
{
    this->chromosomeSize = chromosomeSize;
    this->popSelectionSize = popSelectionSize;
    this->selectionPressure = selectionPressure;
}

std::vector<Chromosome *> Recombination::breedChildChromosomes(std::vector<Chromosome *> parents,
                                                               double populationVariance)
{
    std::vector<Chromosome *> children;
    auto l = 0, r = popSelectionSize - 1;
    while (l < r)
    {
        std::vector<Chromosome *> breedChildren;
        if (populationVariance < selectionPressure)
        {
            breedChildren = cutAndCrossfillCrossover(parents[l], parents[r]);
        }
        else
        {
            breedChildren = cutAndCrossfillCrossover(parents[l], parents[r]);
        }

        children.push_back(breedChildren[0]);
        children.push_back(breedChildren[1]);
        l++;
        r--;
    }

    return children;
}

std::vector<Chromosome *> Recombination::cutAndCrossfillCrossover(
    Chromosome *firstParent,
    Chromosome *secondParent)
{
    Chromosome *firstChildren = new Chromosome(chromosomeSize);
    Chromosome *secondChildren = new Chromosome(chromosomeSize);

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

std::vector<Chromosome *> Recombination::uniformCrossover(
    Chromosome *firstParent,
    Chromosome *secondParent)
{
    Chromosome *firstChildren = new Chromosome(chromosomeSize);
    Chromosome *secondChildren = new Chromosome(chromosomeSize);

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