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

std::vector<std::shared_ptr<Chromosome>> Selection::applyParentSelection(
    std::vector<std::shared_ptr<Chromosome>> &population,
    double populationVariance)
{
    std::vector<std::shared_ptr<Chromosome>> parents;

    if (populationVariance > parentSelectionPressure)
    {
        parents = tournamentParentSelection(population);
    }
    else
    {
        parents = randomParentSelection(population);
    }
    return parents;
}

std::vector<std::shared_ptr<Chromosome>> Selection::applySurvivorSelection(
    std::vector<std::shared_ptr<Chromosome>> &parents,
    std::vector<std::shared_ptr<Chromosome>> &children,
    double populationVariance)
{
    for (const auto &child : children)
    {
        child->calculateFitness();
    }

    std::vector<std::shared_ptr<Chromosome>> survivors;
    if (populationVariance > survivalSelectionPressure)
    {
        // Exploitation
        survivors = crowdingSurvivorSelection(parents, children);
    }
    else
    {
        // Exploration
        survivors = randomSurvivorSelection(parents, children);
    }
    return survivors;
}

std::vector<std::shared_ptr<Chromosome>> Selection::randomParentSelection(
    std::vector<std::shared_ptr<Chromosome>> population)
{
    std::vector<std::shared_ptr<Chromosome>> parents;
    int currentPopSize = popSize - 1;
    for (auto i = 0; i < popSelectionSize; i++)
    {
        auto random = UniformDistributionGenerator::instance()->generate(currentPopSize--);
        parents.push_back(population[random]);
        population.erase(population.begin() + random);
    }
    return parents;
}

std::vector<std::shared_ptr<Chromosome>> Selection::tournamentParentSelection(
    std::vector<std::shared_ptr<Chromosome>> population)
{
    std::vector<std::shared_ptr<Chromosome>> winners;
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

std::vector<std::shared_ptr<Chromosome>> Selection::crowdingSurvivorSelection(
    std::vector<std::shared_ptr<Chromosome>> &parents,
    std::vector<std::shared_ptr<Chromosome>> &children)
{
    std::vector<std::shared_ptr<Chromosome>> survivors;
    for (auto i = 0; i < popSelectionSize; i++)
    {
        auto winner = concludeTournament(parents[i], children[i]);
        survivors.push_back(winner);
    }

    return survivors;
}

std::vector<std::shared_ptr<Chromosome>> Selection::elitistSurvivorSelection(
    std::vector<std::shared_ptr<Chromosome>> &parents,
    std::vector<std::shared_ptr<Chromosome>> &children)
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

std::vector<std::shared_ptr<Chromosome>> Selection::randomSurvivorSelection(
    std::vector<std::shared_ptr<Chromosome>> &parents,
    std::vector<std::shared_ptr<Chromosome>> &children)
{
    std::vector<std::shared_ptr<Chromosome>> survivors;
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

void Selection::selectFittest(std::vector<std::shared_ptr<Chromosome>> &population)
{
    for (auto chromosome : population)
    {
        if (chromosome->fitnessScore > fittestChromosome->fitnessScore)
        {
            fittestChromosome = chromosome;
        }
    }
}

std::shared_ptr<Chromosome> Selection::concludeTournament(
    std::shared_ptr<Chromosome> firstChromosome,
    std::shared_ptr<Chromosome> secondChromosome)
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

void Selection::setFittestChromosome(std::shared_ptr<Chromosome> chromosome)
{
    fittestChromosome = chromosome;
}

std::shared_ptr<Chromosome> Selection::getFittestChromosome()
{
    return fittestChromosome;
}
