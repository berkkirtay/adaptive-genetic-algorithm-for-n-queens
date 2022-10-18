#pragma once
#include "Chromosome.h"
#include "UniformDistributionGenerator.h"
#include <algorithm>

class Selection
{
private:
    int popSize = 0;
    int popSelectionSize = 0;
    double parentSelectionPressure = 0;
    double survivalSelectionPressure = 0;
    Chromosome *fittestChromosome;

public:
    Selection(
        int popSize,
        int popSelectionSize,
        double parentSelectionPressure,
        double survivalSelectionPressure);

    ~Selection();

    std::vector<Chromosome *> applyParentSelection(
        std::vector<Chromosome *> &population,
        double populationVariance);

    std::vector<Chromosome *> applySurvivorSelection(
        std::vector<Chromosome *> &parents,
        std::vector<Chromosome *> &children,
        double populationVariance);

    std::vector<Chromosome *> randomParentSelection(
        std::vector<Chromosome *> population);

    std::vector<Chromosome *> tournamentParentSelection(
        std::vector<Chromosome *> population);

    std::vector<Chromosome *> elitistSurvivorSelection(
        std::vector<Chromosome *> &parents,
        std::vector<Chromosome *> &children);

    std::vector<Chromosome *> crowdingSurvivorSelection(
        std::vector<Chromosome *> &parents,
        std::vector<Chromosome *> &children);

    std::vector<Chromosome *> randomSurvivorSelection(
        std::vector<Chromosome *> &parents,
        std::vector<Chromosome *> &children);

    Chromosome *concludeTournament(
        Chromosome *firstChromosome,
        Chromosome *secondChromosome);

    void selectFittest(std::vector<Chromosome *> &population);

    Chromosome *getFittestChromosome();

    void setFittestChromosome(Chromosome *chromosome);
};
