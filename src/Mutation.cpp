#include "Mutation.h"

Mutation::Mutation(double mutationPressure)
{
    this->mutationPressure = mutationPressure;
}

void Mutation::mutate(std::vector<Chromosome *> &chromosomes, double populationVariance)
{
    if (populationVariance < mutationPressure)
    {
        int tableSize = chromosomes.front()->genes.size();
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