#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int tableSize,
                                   int popSize,
                                   double parentSelectionPressure,
                                   double survivorSelectionPressure,
                                   double mutationPressure)
{
    this->tableSize = tableSize;
    this->popSize = popSize;

    mutation = std::make_unique<Mutation>(Mutation(mutationPressure));
    selection = std::make_unique<Selection>(Selection(parentSelectionPressure,
                                                      survivorSelectionPressure));

    for (int i = 0; i < popSize; i++)
    {
        auto chromosome = new Chromosome(tableSize);
        chromosome->generateRandomly();
        chromosome->index = i;
        chromosome->calculateFitness();
        population.push_back(chromosome);
    }

    selection->setFittestChromosome(population[0]);
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
    for (int i = 0; i < 8000; i++)
    {
        auto parents = selection->applyParentSelection(population, populationVariance);

        auto children = recombination.breedChildChromosomes(parents);
        mutation->mutate(children, populationVariance);

        auto survivors = selection->applySurvivorSelection(parents, children, populationVariance);

        for (int i = 0; i < survivors.size(); i++)
        {
            survivors[i]->index = parents[i]->index;
            population[parents[i]->index] = survivors[i];
            survivors[i] = nullptr;
            delete survivors[i];
        }

        bool isValid = checkFittestChromosome();
        if (isValid == true)
        {
            calculatePopulationDiversity();
            printInfo();
            TableViewConverter::instance()->printValidTable();
            break;
        }

        calculatePopulationDiversity();

        if (i % 100 == 0)
        {
            printInfo();
            means.push_back(populationMean);
            variances.push_back(populationVariance);
        }
    }
}

bool GeneticAlgorithm::checkFittestChromosome()
{
    selection->selectFittest(population);
    return selection->getFittestChromosome()->fitnessScore >= tableSize;
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
