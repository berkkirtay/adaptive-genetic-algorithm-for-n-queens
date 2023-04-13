#include "UniformDistributionGenerator.h"
#include <iostream>

std::shared_ptr<UniformDistributionGenerator> UniformDistributionGenerator::instance()
{

    static std::shared_ptr<UniformDistributionGenerator>
        uniformDistributionGenerator{new UniformDistributionGenerator};
    return uniformDistributionGenerator;
}

std::mt19937 UniformDistributionGenerator::getEngine()
{
    return eng;
}

int UniformDistributionGenerator::generate(int max)
{
    this->max = max;
    if (max == 0)
        return max;
    else
        return dist(eng) % max;
}