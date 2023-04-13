#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include "FitnessChecker.h"
#include "Chromosome.h"
#include "Selection.h"
#include "Mutation.h"
#include "Recombination.h"

class GeneticAlgorithm
{
private:
    int tableSize = 0;
    int popSize = 0;
    double populationVariance = 0;
    double populationMean = 0;
    int numberOfMaxGenerations = 0;
    int generationIndex = 0;
    std::unique_ptr<Selection> selection;
    std::unique_ptr<Recombination> recombination;
    std::unique_ptr<Mutation> mutation;
    std::vector<std::shared_ptr<Chromosome>> population;
    void generateInitialPopulation();
    void printGenerationInfoAndSaveStatistics();
    bool checkFittestChromosome(
        std::vector<std::shared_ptr<Chromosome>> &survivors);
    void calculatePopulationDiversity();
    void removeUnfitChromosomes(
        std::vector<std::shared_ptr<Chromosome>> &parents,
        std::vector<std::shared_ptr<Chromosome>> &survivors);

public:
    std::vector<double> means;
    std::vector<double> variances;
    GeneticAlgorithm(
        int tableSize,
        int popSize,
        double parentSelectionPressure,
        double survivalSelectionPressure,
        double mutationPressure);
    void process();
};
