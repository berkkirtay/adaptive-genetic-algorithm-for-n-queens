#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int tableSize,
                                   int popSize,
                                   double parentSelectionPressure,
                                   double survivorSelectionPressure,
                                   double mutationPressure)
{
    this->tableSize = tableSize;
    this->popSize = popSize;

    auto popSelectionSize = popSize / 10;
    if (popSelectionSize % 2 == 1)
    {
        popSelectionSize++;
    }
    mutation = std::make_unique<Mutation>(Mutation(tableSize, mutationPressure));
    selection = std::make_unique<Selection>(Selection(popSize,
                                                      popSelectionSize,
                                                      parentSelectionPressure,
                                                      survivorSelectionPressure));
    recombination = std::make_unique<Recombination>(Recombination(tableSize,
                                                                  popSelectionSize,
                                                                  parentSelectionPressure));
    generateInitialPopulation();
}

void GeneticAlgorithm::generateInitialPopulation()
{
    for (int i = 0; i < popSize; i++)
    {
        auto chromosome = std::make_shared<Chromosome>(Chromosome(tableSize));
        chromosome->generateRandomly();
        chromosome->index = i;
        chromosome->calculateFitness();
        population.push_back(chromosome);
    }

    selection->setFittestChromosome(population[0]);
}

void GeneticAlgorithm::process()
{
    for (int i = 0; i < 130000; i++)
    {
        // Shuffling the population array emulates the movements in
        // the current population and therefore increases random selection.
        std::shuffle(population.begin(), population.end(),
                     UniformDistributionGenerator::instance()->getEngine());

        auto parents = selection->applyParentSelection(population, populationVariance);
        auto children = recombination->breedChildChromosomes(parents, populationVariance);
        mutation->mutate(children, populationVariance);

        auto survivors = selection->applySurvivorSelection(parents, children, populationVariance);
        removeUnfitChromosomes(parents, survivors);

        if (i % 10 == 0)
            calculatePopulationDiversity();
        bool isValid = checkFittestChromosome();
        if (isValid == true)
        {
            break;
        }

        if (i % 200 == 0)
        {
            printInfo();
            means.push_back(populationMean);
            variances.push_back(populationVariance);
        }
    }
}

void GeneticAlgorithm::removeUnfitChromosomes(std::vector<std::shared_ptr<Chromosome>> &parents,
                                              std::vector<std::shared_ptr<Chromosome>> &survivors)
{
    for (int i = 0; i < static_cast<int>(survivors.size()); i++)
    {
        survivors[i]->index = parents[i]->index;
        population[parents[i]->index] = survivors[i];
    }
}

bool GeneticAlgorithm::checkFittestChromosome()
{
    selection->selectFittest(population);
    auto isComplete = FitnessChecker::instance()->checkSolution(
        selection->getFittestChromosome()->genes);
    if (isComplete == true)
    {
        printInfo();
        TableViewConverter::instance()->printValidTable();
    }
    return isComplete;
}

void GeneticAlgorithm::calculatePopulationDiversity()
{
    double mean = 0;
    double variance = 0;

    for (auto chromosome : population)
    {
        mean += chromosome->fitnessScore;
    }
    mean /= popSize;

    for (auto chromosome : population)
    {
        variance += pow(static_cast<double>(chromosome->fitnessScore) - mean, 2);
    }
    variance /= popSize;
    populationVariance = variance;
    populationMean = mean;
}

void GeneticAlgorithm::printInfo()
{
    std::cout << "Population variance: " << populationVariance
              << " Population mean: " << populationMean << std::endl;
    std::cout << "Score of the fittest chromosome is "
              << selection->getFittestChromosome()->fitnessScore << std::endl;
}
