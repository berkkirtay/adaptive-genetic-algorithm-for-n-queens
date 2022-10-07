#include "Mutation.h"

void Mutation::mutate(std::vector<Chromosome *> &chromosomes, double populationVariance)
{
    int tableSize = chromosomes.front()->genes.size();
    if (populationVariance < 0.6)
    {
        for (auto chromosome : chromosomes)
        {
            int firstRandom = uniformDistGenerator.generate(tableSize - 1);
            int secondRandom = uniformDistGenerator.generate(tableSize - 1);
            int temp = chromosome->genes[firstRandom];
            chromosome->genes[firstRandom] = chromosome->genes[secondRandom];
            chromosome->genes[secondRandom] = temp;
            chromosome->calculateFitness();
        }
    }
}