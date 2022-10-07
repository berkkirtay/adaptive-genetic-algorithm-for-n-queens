#pragma once
#include "Chromosome.h"
#include <algorithm>

class Selection
{
private:
    Chromosome *fittestChromosome;
    UniformDistributionGenerator uniformDistGenerator;

public:
    ~Selection();

    std::vector<Chromosome *> igniteParentSelection(
        std::vector<Chromosome *> population,
        double populationVariance);

    std::vector<Chromosome *> igniteSurvivalSelection(
        std::vector<Chromosome *> parents,
        std::vector<Chromosome *> children,
        double populationVariance);

    std::vector<Chromosome *> randomParentSelection(
        std::vector<Chromosome *> population);

    std::vector<Chromosome *> tournamentParentSelection(
        std::vector<Chromosome *> population);

    std::vector<Chromosome *> elitistSurvivorSelection(
        std::vector<Chromosome *> parents,
        std::vector<Chromosome *> children);

    std::vector<Chromosome *> crowdingSurvivalSelection(
        std::vector<Chromosome *> parents,
        std::vector<Chromosome *> children);

    std::vector<Chromosome *> randomSurvivorSelection(
        std::vector<Chromosome *> parents,
        std::vector<Chromosome *> children);

    Chromosome *concludeTournament(
        Chromosome *firstChromosome,
        Chromosome *secondChromosome);

    void selectFittest(std::vector<Chromosome *> population);

    Chromosome *getFittestChromosome();

    void setFittestChromosome(Chromosome *chromosome);
};
