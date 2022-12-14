#include "UniformDistributionGenerator.h"
#include <iostream>

std::shared_ptr<UniformDistributionGenerator> UniformDistributionGenerator::instance()
{

    static std::shared_ptr<UniformDistributionGenerator> uniformDistributionGenerator{new UniformDistributionGenerator};
    return uniformDistributionGenerator;
}

std::mt19937 UniformDistributionGenerator::getEngine()
{
    return eng;
}

int UniformDistributionGenerator::generate(int max)
{
    // srand(time(NULL));
    // auto a = rand() % max;
    //  std::cout << a << std::endl;
    //  return a;
    this->max = max;
    if (max == 0)
        return max;
    else
        return dist(eng) % max;
}