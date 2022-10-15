#include "UniformDistributionGenerator.h"

UniformDistributionGenerator::UniformDistributionGenerator()
{
    // std::mt19937::result_type seed = time(NULL);
}

std::shared_ptr<UniformDistributionGenerator> UniformDistributionGenerator::instance()
{
    static std::shared_ptr<UniformDistributionGenerator> uniformDistributionGenerator{new UniformDistributionGenerator};
    return uniformDistributionGenerator;
}

int UniformDistributionGenerator::generate(int max)
{
    this->max = max;
    if (max == 0)
        return max;
    else
        return std::uniform_int_distribution<int>{0, max}(eng);
}