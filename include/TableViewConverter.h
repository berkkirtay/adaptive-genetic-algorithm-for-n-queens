#pragma once
#include <vector>
#include <iostream>
#include <memory>

class TableViewConverter
{
private:
    TableViewConverter();

public:
    TableViewConverter(TableViewConverter const &) = delete;
    TableViewConverter &operator=(TableViewConverter const &) = delete;
    static std::shared_ptr<TableViewConverter> instance();
    void convertToTable(std::vector<int> genes);
    std::vector<std::string> validTable;
    void printValidTable();
};