// Copyright (c) 2022 Berk Kirtay

#pragma once
#include <random>
#include <ctime>
#include <memory>

class UniformDistributionGenerator
{
private:
    explicit UniformDistributionGenerator() : eng{randomDevice()}, dist{0, 100000} {};
    std::mt19937 eng;
    std::uniform_int_distribution<int> dist;
    std::random_device randomDevice;

public:
    int max = 0;
    int generate(int max);
    std::mt19937 getEngine();
    UniformDistributionGenerator(UniformDistributionGenerator const &) = delete;
    UniformDistributionGenerator &operator=(UniformDistributionGenerator const &) = delete;
    static std::shared_ptr<UniformDistributionGenerator> instance();
};
