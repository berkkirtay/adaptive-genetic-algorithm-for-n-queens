#pragma once
#include <vector>
#include <iostream>

class SolutionChecker {
public:
    bool checkSolution(std::vector<std::string> solution);
    int checkAndReturnLastIndex(std::vector<std::string> solution);

private:
    int lastIndex = 0;
    bool isAValidPlacement(int i, int j, int n, std::vector<std::string> curr);
};