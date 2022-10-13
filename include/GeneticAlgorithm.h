#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "FitnessChecker.h"
#include "Chromosome.h"
#include "Selection.h"
#include "Mutation.h"
#include "Recombination.h"

class GeneticAlgorithm
{
private:
    int tableSize = 1;
    int popSize = 0;
    double populationVariance = 0;
    double populationMean = 0;
    std::unique_ptr<Mutation> mutation;
    std::unique_ptr<Selection> selection;
    Recombination recombination;
    std::vector<Chromosome *> population;
    UniformDistributionGenerator uniformDistGenerator;
    void printInfo();
    bool checkFittestChromosome();
    void calculatePopulationDiversity();

public:
    std::vector<double> means;
    std::vector<double> variances;
    GeneticAlgorithm(int tableSize,
                     int popSize,
                     double parentSelectionPressure,
                     double survivalSelectionPressure,
                     double mutationPressure);
    ~GeneticAlgorithm();
    void process();
};
