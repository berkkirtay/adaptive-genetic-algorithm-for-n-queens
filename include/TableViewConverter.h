#pragma once
#include "SolutionChecker.h"
#include <memory>

class TableViewConverter
{
private:
	TableViewConverter() {}
	SolutionChecker sc;
	std::vector<std::string> convertToTable(std::vector<int> genes);

public:
	TableViewConverter(TableViewConverter const &) = delete;
	TableViewConverter &operator=(TableViewConverter const &) = delete;
	static std::shared_ptr<TableViewConverter> instance();
	int lastIndex = 0;
	std::vector<std::string> validTable;
	bool validateSolution(std::vector<int> genes);
	void printValidTable();
};