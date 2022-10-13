#include "Recombination.h"

std::vector<Chromosome *> Recombination::breedChildChromosomes(std::vector<Chromosome *> parents)
{
    std::vector<Chromosome *> children;
    int l = 0, r = parents.size() - 1;
    while (l < r)
    {
        auto breedChildren = uniformCrossover(parents[l], parents[r]);
        breedChildren[0]->calculateFitness();
        breedChildren[1]->calculateFitness();
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
    int genesSize = firstParent->genes.size();

    Chromosome *firstChildren = new Chromosome(genesSize);
    Chromosome *secondChildren = new Chromosome(genesSize);

    int random = uniformDistGenerator.generate(genesSize - 1);

    for (int i = 0; i < random; i++)
    {
        firstChildren->genes[i] = firstParent->genes[i];
        secondChildren->genes[i] = secondParent->genes[i];
    }

    for (int i = random; i < genesSize; i++)
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
    int genesSize = firstParent->genes.size();

    Chromosome *firstChildren = new Chromosome(genesSize);
    Chromosome *secondChildren = new Chromosome(genesSize);

    for (int i = 0; i < genesSize; i++)
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