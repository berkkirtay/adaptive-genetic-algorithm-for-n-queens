// Copyright (c) 2022 Berk Kırtay

#include <vector>
#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "GeneticAlgorithm.h"

std::vector<double> parseArgs(int argc, char **argv);
void exportData(
    std::vector<double> means,
    std::vector<double> variances);

int main(int argc, char **argv)
{
    auto parameters = parseArgs(argc, argv);
    /*
        int tableSize = 100;
        int popSize = 1000;
        double parentSelectionPressure = 8;
        double survivorSelectionPressure = 7;
        double mutationPressure = 30;
    */

    int tableSize = static_cast<int>(parameters[0]);
    int popSize = static_cast<int>(parameters[1]);
    double parentSelectionPressure = parameters[2];
    double survivorSelectionPressure = parameters[3];
    double mutationPressure = parameters[4];

    std::cout
        << "Table size: "
        << tableSize << std::endl
        << "Population Size: "
        << popSize << std::endl
        << "Parent Selection Pressure: "
        << parentSelectionPressure << std::endl
        << "Survivor Selection Pressure: "
        << survivorSelectionPressure << std::endl
        << "Mutation Pressure: "
        << mutationPressure << std::endl
        << "\n\n"
        << std::endl;

    GeneticAlgorithm ga(
        tableSize,
        popSize,
        parentSelectionPressure,
        survivorSelectionPressure,
        mutationPressure);

    using namespace std::chrono;
    auto begin = steady_clock::now();
    ga.process();
    auto end = steady_clock::now();

    auto runtime = duration_cast<milliseconds>(end - begin).count();
    std::cout
        << "Runtime: "
        << (double)runtime / 1000
        << " seconds." << std::endl;

    exportData(ga.means, ga.variances);
    return 0;
}

std::vector<double> parseArgs(int argc, char **argv)
{
    std::stringstream builder;
    builder << "Usage: "
            << "{-t, --tablesize} {value} "
            << "{-p, --popsize} {value} "
            << "{-pp, --parentselectionpressure} {value} "
            << "{-sp, --survivorselectionpressure} {value} "
            << "{-mp, --mutationpressure} {value} ";

    std::string usage = builder.str();

    if (argc != 11)
    {
        std::cout
            << "FAILURE: Incorrect number of arguments!\n"
            << argc << " given, 11 required.\n"
            << usage
            << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> args(argv + 1, argv + argc);
    std::unordered_map<std::string, bool> map;
    std::vector<double> parameters(5);
    std::string lastArg;

    try
    {
        for (auto arg : args)
        {
            if (!lastArg.empty())
            {
                if (map[lastArg] == false)
                {
                    map[lastArg] = true;
                    double parameter = std::stod(arg);
                    if (lastArg == "-t")
                        parameters[0] = parameter;
                    else if (lastArg == "-p")
                        parameters[1] = parameter;
                    else if (lastArg == "-pp")
                        parameters[2] = parameter;
                    else if (lastArg == "-sp")
                        parameters[3] = parameter;
                    else if (lastArg == "-mp")
                        parameters[4] = parameter;
                    lastArg.clear();
                }
                else
                {
                    std::cout
                        << "FAILURE: Each command argument can be used only one time!\n"
                        << usage
                        << std::endl;
                    exit(EXIT_FAILURE);
                }
            }

            if (arg == "-t" || arg == "--tablesize")
            {
                lastArg = "-t";
            }

            else if (arg == "-p" || arg == "--popsize")
            {
                lastArg = "-p";
            }

            else if (arg == "-pp" || arg == "--parentselectionpressure")
            {
                lastArg = "-pp";
            }

            else if (arg == "-sp" || arg == "--survivorselectionpressur")
            {
                lastArg = "-sp";
            }

            else if (arg == "-mp" || arg == "--mutationpressure")
            {
                lastArg = "-mp";
            }
        }
    }
    catch (std::exception &ex)
    {
        std::cout
            << ex.what()
            << "\n"
            << usage
            << std::endl;
        exit(EXIT_FAILURE);
    }

    return parameters;
}

void exportData(
    std::vector<double> means,
    std::vector<double> variances)
{
    std::ofstream file;
    file.open("../chart/data.csv");
    int size = static_cast<int>(means.size());
    for (auto i = 0; i < size; i++)
    {
        if (i == size - 1)
            file << means[i];
        else
            file << means[i] << ",";
    }

    file << std::endl;

    for (auto i = 0; i < size; i++)
    {
        if (i == size - 1)
            file << variances[i];
        else
            file << variances[i] << ",";
    }

    file.close();
}