#pragma once
#include <random>
#include <ctime>

class UniformDistributionGenerator
{
private:
    std::mt19937 eng{std::random_device{}()};

public:
    int max;
    UniformDistributionGenerator();
    int generate(unsigned int max);
};
