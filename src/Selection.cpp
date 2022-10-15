#include "Selection.h"

Selection::Selection(
    int popSize,
    int popSelectionSize,
    double parentSelectionPressure,
    double survivalSelectionPressure)
{
    this->popSize = popSize;
    this->popSelectionSize = popSelectionSize;
    this->parentSelectionPressure = parentSelectionPressure;
    this->survivalSelectionPressure = survivalSelectionPressure;
}

Selection::~Selection()
{
    delete fittestChromosome;
}

std::vector<Chromosome *> Selection::applyParentSelection(
    std::vector<Chromosome *> population, double populationVariance)
{
    std::vector<Chromosome *> parents;

    if (populationVariance < parentSelectionPressure)
    {
        parents = randomParentSelection(population);
    }
    else
    {
        parents = tournamentParentSelection(population);
    }
    return parents;
}

std::vector<Chromosome *> Selection::applySurvivorSelection(
    std::vector<Chromosome *> parents, std::vector<Chromosome *> children, double populationVariance)
{
    for (const auto &child : children)
    {
        child->calculateFitness();
    }

    std::vector<Chromosome *> survivors;
    if (populationVariance < survivalSelectionPressure)
    {
        // Exploration
        survivors = randomSurvivorSelection(parents, children);
    }
    else if (populationVariance >=
             survivalSelectionPressure * survivalSelectionPressure)
    {
        // Exploitation
        survivors = crowdingSurvivorSelection(parents, children);
    }
    else
    {
        // Exploitation
        survivors = elitistSurvivorSelection(parents, children);
    }
    return survivors;
}

std::vector<Chromosome *> Selection::randomParentSelection(std::vector<Chromosome *> population)
{
    std::vector<Chromosome *> parents;
    int currentPopSize = popSize - 1;
    for (auto i = 0; i < popSelectionSize; i++)
    {
        auto random = UniformDistributionGenerator::instance()->generate(currentPopSize--);
        parents.push_back(population[random]);
        population.erase(population.begin() + random);
    }
    return parents;
}

std::vector<Chromosome *> Selection::tournamentParentSelection(
    std::vector<Chromosome *> population)
{
    std::vector<Chromosome *> winners;
    int currentPopSize = popSize - 1;
    // The random number generator should not generate a
    // same parent twice. So we erase the chosen parent
    // from the given population in this scope.

    for (int i = 0; i < popSelectionSize; i++)
    {
        auto random = UniformDistributionGenerator::instance()->generate(currentPopSize--);
        auto firstParent = population[random];
        population.erase(population.begin() + random);

        random = UniformDistributionGenerator::instance()->generate(currentPopSize--);
        auto secondParent = population[random];
        population.erase(population.begin() + random);

        auto winner = concludeTournament(firstParent, secondParent);
        winners.push_back(winner);
    }
    return winners;
}

std::vector<Chromosome *> Selection::crowdingSurvivorSelection(
    std::vector<Chromosome *> parents,
    std::vector<Chromosome *> children)
{
    std::vector<Chromosome *> survivors;
    for (auto i = 0; i < popSelectionSize; i++)
    {
        auto winner = concludeTournament(parents[i], children[i]);
        survivors.push_back(winner);
    }

    return survivors;
}

std::vector<Chromosome *> Selection::elitistSurvivorSelection(
    std::vector<Chromosome *> parents,
    std::vector<Chromosome *> children)
{
    for (auto child : children)
    {
        child->calculateFitness();
        parents.push_back(child);
    }

    std::sort(parents.begin(),
              parents.end(),
              Chromosome::compare);

    parents.erase(parents.begin() + parents.size() / 2, parents.end());
    return parents;
}

std::vector<Chromosome *> Selection::randomSurvivorSelection(
    std::vector<Chromosome *> parents,
    std::vector<Chromosome *> children)
{
    std::vector<Chromosome *> survivors;
    for (auto i = 0; i < popSelectionSize; i++)
    {
        auto random = UniformDistributionGenerator::instance()->generate(10);
        if (random >= 5)
        {
            survivors.push_back(parents[i]);
        }
        else
        {
            survivors.push_back(children[i]);
        }
    }
    return survivors;
}

void Selection::selectFittest(std::vector<Chromosome *> population)
{
    for (auto chromosome : population)
    {
        if (chromosome->fitnessScore > fittestChromosome->fitnessScore)
        {
            fittestChromosome = chromosome;
        }
    }
}

Chromosome *Selection::concludeTournament(
    Chromosome *firstChromosome,
    Chromosome *secondChromosome)
{
    if (firstChromosome->fitnessScore > secondChromosome->fitnessScore)
    {
        return firstChromosome;
    }
    else
    {
        return secondChromosome;
    }
}

void Selection::setFittestChromosome(Chromosome *chromosome)
{
    fittestChromosome = chromosome;
}

Chromosome *Selection::getFittestChromosome()
{
    return fittestChromosome;
}
