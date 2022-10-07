#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int tableSize, int popSize)
{
	this->tableSize = tableSize;
	this->popSize = popSize;

	for (int i = 0; i < popSize; i++)
	{
		auto chromosome = new Chromosome(tableSize);
		chromosome->generateRandomly();
		chromosome->index = i;
		chromosome->calculateFitness();
		population.push_back(chromosome);
	}

	selection.setCurrentBestsolution(population[0]);
}

GeneticAlgorithm::~GeneticAlgorithm()
{
	for (auto chromosome : population)
	{
		delete chromosome;
	}
}

void GeneticAlgorithm::process()
{
	for (int i = 0; i < 30000; i++)
	{
		std::vector<Chromosome *> parents;

		if (populationDiversity < 1)
		{
			parents = selection.tournamentParentSelection(population);
		}
		else
		{
			parents = selection.randomParentSelection(population);
		}

		std::vector<Chromosome *> children = breedChildChromosomes(parents);
		mutation(children);

		std::vector<Chromosome *> survivors;
		if (populationDiversity < 0.3)
		{
			survivors = selection.randomSurvivorSelection(parents, children);
		}
		else
		{
			survivors = selection.crowdingSurvivalSelection(parents, children);
		}

		for (int i = 0; i < survivors.size(); i++)
		{
			survivors[i]->index = parents[i]->index;
			population[parents[i]->index] = survivors[i];
			survivors[i] = nullptr;
			delete survivors[i];
		}

		// delete parents[0];
		selection.selectBest(population);
		if (i % 10 == 0)
		{
			calculatePopulationDiversity();
			selection.selectBest(population);
			if (selection.getCurrentBestsolution()->fitnessScore >= tableSize - 1)
				break;
			tvc.convertAndPrint(
				selection.getCurrentBestsolution()->genes);
		}
	}
}

void GeneticAlgorithm::calculatePopulationDiversity()
{
	int mean = 0;
	for (auto chromosome : population)
	{
		mean += chromosome->fitnessScore;
	}
	mean /= popSize;

	double variance = 0;
	for (auto chromosome : population)
	{
		variance += (chromosome->fitnessScore - mean) < 1;
	}

	variance /= popSize;

	populationDiversity = variance;
}

std::vector<Chromosome *> GeneticAlgorithm::breedChildChromosomes(std::vector<Chromosome *> parents)
{
	std::vector<Chromosome *> children;
	int l = 0, r = parents.size() - 1;
	while (l < r)
	{
		auto breedChildren = cutAndCrossfillCrossover(parents[l], parents[r]);
		children.push_back(breedChildren[0]);
		children.push_back(breedChildren[1]);
		l++;
		r--;
	}

	return children;
}

std::vector<Chromosome *> GeneticAlgorithm::cutAndCrossfillCrossover(
	Chromosome *firstParent,
	Chromosome *secondParent)
{
	std::vector<Chromosome *> children;
	int genesSize = firstParent->genes.size();
	int random = uniformDistGenerator.generate(genesSize - 1);

	std::vector<int> firstChildsGenes(genesSize);
	std::vector<int> secondtChildsGenes(genesSize);

	for (int i = 0; i < random; i++)
	{
		firstChildsGenes[i] = firstParent->genes[i];
		secondtChildsGenes[i] = secondParent->genes[i];
	}

	for (int i = random; i < genesSize; i++)
	{
		firstChildsGenes[i] = secondParent->genes[i];
		secondtChildsGenes[i] = firstParent->genes[i];
	}

	auto firstChild = new Chromosome(genesSize);
	firstChild->copyGenes(firstChildsGenes);
	auto secondChild = new Chromosome(genesSize);
	secondChild->copyGenes(secondtChildsGenes);

	children.push_back(firstChild);
	children.push_back(secondChild);
	return children;
}

void GeneticAlgorithm::mutation(std::vector<Chromosome *> &chromosomes)
{
	int random = uniformDistGenerator.generate(tableSize - 1);
	if (random < uniformDistGenerator.max / 2)
	{
		for (auto chromosome : chromosomes)
		{
			int firstRandom = uniformDistGenerator.generate(tableSize - 1);
			int secondRandom = uniformDistGenerator.generate(tableSize - 1);
			int temp = chromosome->genes[firstRandom];
			chromosome->genes[firstRandom] = chromosome->genes[secondRandom];
			chromosome->genes[secondRandom] = temp;
			chromosome->calculateFitness();
		}
	}
}
