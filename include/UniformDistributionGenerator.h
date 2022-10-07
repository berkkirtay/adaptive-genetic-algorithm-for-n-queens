#pragma once
#include <random>
#include <ctime>

class UniformDistributionGenerator
{
private:
    std::mt19937 eng{std::random_device{}()};

public:
    int max = 0;
    UniformDistributionGenerator();
    int generate(int max);
};
