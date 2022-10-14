#include "FitnessChecker.h"

FitnessChecker::FitnessChecker() {}

std::shared_ptr<FitnessChecker>
FitnessChecker::instance()
{
    static std::shared_ptr<FitnessChecker> fitnessChecker{new FitnessChecker};
    return fitnessChecker;
}

void FitnessChecker::checkSolution(std::vector<int> genes)
{
    currentFitnessScore = calculateFitnessFunction(genes);

    if (currentFitnessScore == genes.size())
    {
        TableViewConverter::instance()->convertToTable(genes);
    }
}

int FitnessChecker::calculateFitnessFunction(std::vector<int> genes)
{
    int penalty = 0;
    int size = static_cast<int>(genes.size());

    for (int i = 0; i < size; i++)
    {
        int j = 1;
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