#pragma once
#include "FitnessChecker.h"
#include "UniformDistributionGenerator.h"
#include <memory>

class Chromosome
{
public:
    std::vector<int> genes;
    int size = 0;
    int index = 0;
    int fitnessScore = 0;

    Chromosome(int size);
    void generateRandomly();
    void copy(std::shared_ptr<Chromosome> chromosome);
    void copyGenes(std::vector<int> genes);
    void calculateFitness();
    static bool compare(const std::shared_ptr<Chromosome> a, const std::shared_ptr<Chromosome> b);
};
