#include "TableViewConverter.h"

std::shared_ptr<TableViewConverter> TableViewConverter::instance()
{
	static std::shared_ptr<TableViewConverter> tvc{new TableViewConverter};
	return tvc;
}

std::vector<std::string> TableViewConverter::convertToTable(std::vector<int> genes)
{
	std::vector<std::string> solution;
	for (int i = 0; i < genes.size(); i++)
	{
		std::string row = "";
		for (int j = 0; j < genes.size(); j++)
		{
			row += '-';
		}
		row[genes[i]] = 'Q';
		solution.push_back(row);
	}
	return solution;
}

bool TableViewConverter::validateSolution(std::vector<int> genes)
{
	auto table = convertToTable(genes);
	lastIndex = sc.checkAndReturnLastIndex(table);

	if (lastIndex == table.size() - 1)
	{
		std::cout
			<< "A valid table is constructed!"
			<< std::endl;

		validTable = table;
		return true;
	}
	return false;
}

void TableViewConverter::printValidTable()
{
	std::cout << "Table View: " << std::endl;
	for (auto &str : validTable)
	{
		std::cout << str << std::endl;
	}
}