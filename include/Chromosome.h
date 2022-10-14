#pragma once
#include "FitnessChecker.h"
#include "UniformDistributionGenerator.h"

class Chromosome
{
private:
    UniformDistributionGenerator uniformDistGenerator;

public:
    std::vector<int> genes;
    int size = 0;
    int index = 0;
    int fitnessScore = 0;

    Chromosome(int size);
    void generateRandomly();
    void copy(Chromosome chromosome);
    void copyGenes(std::vector<int> genes);
    void calculateFitness();
    static bool compare(const Chromosome *a, const Chromosome *b);
};
