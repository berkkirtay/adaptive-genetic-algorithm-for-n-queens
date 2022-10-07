#pragma once
#include "Chromosome.h"
#include <algorithm>

class Selection
{
private:
	Chromosome * currentBestSolution;
	UniformDistributionGenerator uniformDistGenerator;
public:
	std::vector<Chromosome*> randomParentSelection(
		std::vector<Chromosome*> population);

	std::vector<Chromosome*> tournamentParentSelection(
		std::vector<Chromosome*> population);

	std::vector<Chromosome*> elitistSurvivorSelection(
		std::vector<Chromosome*> parents, 
		std::vector<Chromosome*> children);

	std::vector<Chromosome*> crowdingSurvivalSelection(
		std::vector<Chromosome*> parents,
		std::vector<Chromosome*> children);

	std::vector<Chromosome*> randomSurvivorSelection(
		std::vector<Chromosome*> parents,
		std::vector<Chromosome*> children);

	Chromosome* concludeTournament(
		Chromosome* firstChromosome,
		Chromosome* secondChromosome);

	void selectBest(std::vector<Chromosome*> population);

	Chromosome* getCurrentBestsolution();

	void setCurrentBestsolution(Chromosome* chromosome);
};

