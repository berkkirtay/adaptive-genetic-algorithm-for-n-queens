#pragma once
#include <random>
#include <ctime>
#include <memory>

class UniformDistributionGenerator
{
private:
    UniformDistributionGenerator();
    std::mt19937 eng{std::random_device{}()};

public:
    int max = 0;
    int generate(int max);
    UniformDistributionGenerator(UniformDistributionGenerator const &) = delete;
    UniformDistributionGenerator &operator=(UniformDistributionGenerator const &) = delete;
    static std::shared_ptr<UniformDistributionGenerator> instance();
};
