#pragma once
#include <vector>
#include <iostream>

class FitnessChecker
{
public:
    int calculateFitnessFunction(std::vector<std::string> solution);

private:
    bool isAValidPlacement(int i, int j, int n, std::vector<std::string> curr);
};