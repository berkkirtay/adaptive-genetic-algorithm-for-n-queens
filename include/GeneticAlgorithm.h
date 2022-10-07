#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "SolutionChecker.h"
#include "Chromosome.h"
#include "Selection.h"

class GeneticAlgorithm {
private:
	int tableSize = 1;
	int popSize = 0;
	double populationDiversity;
	TableViewConverter tvc;
	Selection selection;
	UniformDistributionGenerator uniformDistGenerator;
	std::vector<Chromosome *> population;

public:
	GeneticAlgorithm(int tableSize, int popSize);
	~GeneticAlgorithm();
	void process();
	void calculatePopulationDiversity();
	std::vector<Chromosome*> breedChildChromosomes(std::vector<Chromosome*> parents);
	std::vector<Chromosome*> cutAndCrossfillCrossover(Chromosome* firstParent, Chromosome* secondParent);
	void mutation(std::vector<Chromosome*>& chromosomes);
};
