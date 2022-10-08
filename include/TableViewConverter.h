#pragma once
#include "FitnessChecker.h"
#include <memory>

class TableViewConverter
{
private:
    TableViewConverter() {}
    FitnessChecker sc;
    std::vector<std::string> convertToTable(std::vector<int> genes);

public:
    TableViewConverter(TableViewConverter const &) = delete;
    TableViewConverter &operator=(TableViewConverter const &) = delete;
    static std::shared_ptr<TableViewConverter> instance();
    int currentFitnessScore = 0;
    std::vector<std::string> validTable;
    bool validateSolution(std::vector<int> genes);
    void printValidTable();
};