#include "TableViewConverter.h"

int TableViewConverter::convertAndPrint(std::vector<int> genes)
{
	std::vector<std::string> solution;
	for (int i = 0; i < genes.size(); i++)
	{
		std::string row = "";
		for (int j = 0; j < genes.size(); j++)
		{
			row += '.';
		}
		row[genes[i]] = 'Q';
		solution.push_back(row);
	}

	int result = sc.checkAndReturnLastIndex(solution);
	if (result >= genes.size() - 1)
	{
		std::cout << "Solution is valid!" << std::endl;
		for (auto str : solution)
		{
			std::cout << str << std::endl;
		}
	}
	else
	{
		//	std::cout << "Solution is invalid!" << std::endl;
	}
	return result;
}