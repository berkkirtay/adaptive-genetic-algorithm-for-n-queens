#pragma once
#include <vector>
#include <iostream>
#include "TableViewConverter.h"

class FitnessChecker
{
private:
    FitnessChecker();

public:
    FitnessChecker(FitnessChecker const &) = delete;
    FitnessChecker &operator=(FitnessChecker const &) = delete;
    static std::shared_ptr<FitnessChecker> instance();
    bool checkSolution(std::vector<int> genes);
    int calculateFitnessFunction(std::vector<int> genes);
    int currentFitnessScore = 0;
};