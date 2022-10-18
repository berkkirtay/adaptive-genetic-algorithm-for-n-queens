#include "FitnessChecker.h"

FitnessChecker::FitnessChecker() {}

std::shared_ptr<FitnessChecker>
FitnessChecker::instance()
{
    static std::shared_ptr<FitnessChecker> fitnessChecker{new FitnessChecker};
    return fitnessChecker;
}

bool FitnessChecker::checkSolution(std::vector<int> &genes)
{
    currentFitnessScore = calculateFitnessFunction(genes);
    auto isComplete = currentFitnessScore == static_cast<int>(genes.size());
    if (isComplete == true)
    {
        TableViewConverter::instance()->convertToTable(genes);
    }
    return isComplete;
}

int FitnessChecker::calculateFitnessFunction(std::vector<int> &genes)
{
    auto penalty = 0;
    auto size = static_cast<int>(genes.size());

    for (auto i = 0; i < size; i++)
    {
        auto j = 1;
        while (j < i)
        {
            if (!(genes[i - j] != genes[i] - j &&
                  genes[i - j] != genes[i] + j &&
                  genes[i - j] != genes[i]))
            {
                penalty++;
            }
            j++;
        }
    }
    return size - penalty;
}