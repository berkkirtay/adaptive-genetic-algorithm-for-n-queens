#include "Recombination.h"

std::vector<Chromosome *> Recombination::breedChildChromosomes(std::vector<Chromosome *> parents)
{
    std::vector<Chromosome *> children;
    int l = 0, r = parents.size() - 1;
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

std::vector<Chromosome *> Recombination::cutAndCrossfillCrossover(
    Chromosome *firstParent,
    Chromosome *secondParent)
{
    std::vector<Chromosome *> children;
    int genesSize = firstParent->genes.size();
    int random = uniformDistGenerator.generate(genesSize - 1);

    std::vector<int> firstChildsGenes(genesSize);
    std::vector<int> secondtChildsGenes(genesSize);

    for (int i = 0; i < random; i++)
    {
        firstChildsGenes[i] = firstParent->genes[i];
        secondtChildsGenes[i] = secondParent->genes[i];
    }

    for (int i = random; i < genesSize; i++)
    {
        firstChildsGenes[i] = secondParent->genes[i];
        secondtChildsGenes[i] = firstParent->genes[i];
    }

    auto firstChild = new Chromosome(genesSize);
    firstChild->copyGenes(firstChildsGenes);
    auto secondChild = new Chromosome(genesSize);
    secondChild->copyGenes(secondtChildsGenes);

    children.push_back(firstChild);
    children.push_back(secondChild);
    return children;
}