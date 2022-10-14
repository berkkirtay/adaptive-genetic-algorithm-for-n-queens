#include "Chromosome.h"

Chromosome::Chromosome(int size)
{
    this->size = size;
    genes.resize(size, 0);
}

void Chromosome::generateRandomly()
{
    std::vector<int> sampledGenes;
    for (int i = 0; i < size; i++)
    {
        sampledGenes.push_back(i);
    }

    for (int i = 0; i < size; i++)
    {
        if (sampledGenes.size() == 1)
        {
            genes[i] = sampledGenes[0];
        }
        else
        {
            int random = uniformDistGenerator.generate(sampledGenes.size() - 1);
            genes[i] = sampledGenes[random];
            sampledGenes.erase(sampledGenes.begin() + random);
        }
    }
    calculateFitness();
}

void Chromosome::copy(Chromosome chromosome)
{
    for (int i = 0; i < chromosome.size; i++)
    {
        genes[i] = chromosome.genes[i];
    }
    index = chromosome.index;
    fitnessScore = chromosome.fitnessScore;
}

void Chromosome::copyGenes(std::vector<int> genes)
{
    this->genes = genes;
    calculateFitness();
}

void Chromosome::calculateFitness()
{
    FitnessChecker::instance()->checkSolution(genes);
    fitnessScore = FitnessChecker::instance()->currentFitnessScore;
}

bool Chromosome::compare(const Chromosome *a, const Chromosome *b)
{
    return a->fitnessScore > b->fitnessScore;
}

/*
bool Chromosome:: operator > (const Chromosome chromosome) const
{
    return fitnessScore > chromosome.fitnessScore;
}
*/
