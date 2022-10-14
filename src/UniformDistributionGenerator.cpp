#include "UniformDistributionGenerator.h"

UniformDistributionGenerator::UniformDistributionGenerator()
{
    std::mt19937::result_type seed = time(NULL);
}

int UniformDistributionGenerator::generate(int max)
{
    this->max = max;
    if (max == 0)
        return max;
    else
        return std::uniform_int_distribution<int>{0, max}(eng);
}