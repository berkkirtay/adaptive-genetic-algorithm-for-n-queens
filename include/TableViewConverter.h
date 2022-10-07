#pragma once
#include "SolutionChecker.h"

class TableViewConverter
{
private:
	SolutionChecker sc;

public:
	int convertAndPrint(std::vector<int> genes);
};