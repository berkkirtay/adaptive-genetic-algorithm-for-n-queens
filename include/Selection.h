// Copyright (c) 2022 Berk Kirtay

#pragma once
#include "Chromosome.h"
#include "UniformDistributionGenerator.h"
#include <algorithm>
#include <memory>

class Selection
{
private:
    int popSize = 0;
    int popSelectionSize = 0;
    double parentSelectionPressure = 0;
    double survivalSelectionPressure = 0;
    std::shared_ptr<Chromosome> fittestChromosome;

public:
    Selection(
        int popSize,
        int popSelectionSize,
        double parentSelectionPressure,
        double survivalSelectionPressure);

    std::vector<std::shared_ptr<Chromosome>> applyParentSelection(
        std::vector<std::shared_ptr<Chromosome>> &population,
        double populationVariance);

    std::vector<std::shared_ptr<Chromosome>> applySurvivorSelection(
        std::vector<std::shared_ptr<Chromosome>> &parents,
        std::vector<std::shared_ptr<Chromosome>> &children,
        double populationVariance);

    std::vector<std::shared_ptr<Chromosome>> randomParentSelection(
        std::vector<std::shared_ptr<Chromosome>> population);

    std::vector<std::shared_ptr<Chromosome>> tournamentParentSelection(
        std::vector<std::shared_ptr<Chromosome>> population);

    std::vector<std::shared_ptr<Chromosome>> elitistSurvivorSelection(
        std::vector<std::shared_ptr<Chromosome>> &parents,
        std::vector<std::shared_ptr<Chromosome>> &children);

    std::vector<std::shared_ptr<Chromosome>> crowdingSurvivorSelection(
        std::vector<std::shared_ptr<Chromosome>> &parents,
        std::vector<std::shared_ptr<Chromosome>> &children);

    std::vector<std::shared_ptr<Chromosome>> randomSurvivorSelection(
        std::vector<std::shared_ptr<Chromosome>> &parents,
        std::vector<std::shared_ptr<Chromosome>> &children);

    std::shared_ptr<Chromosome> concludeTournament(
        std::shared_ptr<Chromosome> firstChromosome,
        std::shared_ptr<Chromosome> secondChromosome);

    void selectFittest(std::vector<std::shared_ptr<Chromosome>> &population);

    std::shared_ptr<Chromosome> getFittestChromosome();

    void setFittestChromosome(std::shared_ptr<Chromosome> chromosome);
};
