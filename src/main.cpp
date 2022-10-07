#include <vector>
#include <iostream>
#include <chrono>
#include <fstream>
#include "BacktrackingAlgorithm.h"
#include "GeneticAlgorithm.h"

void exportData(std::vector<double> means, std::vector<double> variances);

int main()
{
    // BacktrackingAlgorithm backtrackingAlgorithm;
    //  backtrackingAlgorithm.solveNQueens(10);
    int tableSize = 15;
    double populationEquation = floor(pow(1.4, tableSize));
    int popSize = floor(tableSize * populationEquation);

    std::cout
        << "Table size: " << tableSize << std::endl
        << "Population Size: " << popSize << std::endl;

    GeneticAlgorithm ga(tableSize, popSize);

    auto begin = std::chrono::steady_clock::now();
    ga.process();
    auto end = std::chrono::steady_clock::now();

    auto runtime = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
    std::cout << "Runtime: " << runtime << " seconds." << std::endl;

    exportData(ga.means, ga.variances);
    return 0;
}

void exportData(std::vector<double> means, std::vector<double> variances)
{
    std::ofstream file;
    file.open("../chart/data.csv");
    for (auto mean : means)
    {
        file << mean << ",";
    }

    file << std::endl;

    for (auto variance : variances)
    {
        file << variance << ",";
    }

    file.close();
}