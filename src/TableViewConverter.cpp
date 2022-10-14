#include "TableViewConverter.h"

TableViewConverter::TableViewConverter() {}

std::shared_ptr<TableViewConverter>
TableViewConverter::instance()
{
    static std::shared_ptr<TableViewConverter> tvc{new TableViewConverter};
    return tvc;
}

void TableViewConverter::convertToTable(std::vector<int> genes)
{
    std::vector<std::string> table;
    for (int i = 0; i < genes.size(); i++)
    {
        std::string row = "";
        for (int j = 0; j < genes.size(); j++)
        {
            row += '-';
        }
        row[genes[i]] = 'Q';
        table.push_back(row);
    }
    validTable = table;
}

void TableViewConverter::printValidTable()
{
    std::cout
        << "A valid table is constructed!"
        << std::endl
        << "Table View:"
        << std::endl;

    for (auto str : validTable)
    {
        std::cout << str << std::endl;
    }
}