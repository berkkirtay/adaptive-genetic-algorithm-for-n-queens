#pragma once
#include <vector>
#include <iostream>
#include "SolutionChecker.h"

class BacktrackingAlgorithm
{
private:
    SolutionChecker sc;

public:
    std::vector<std::vector<std::string>> solveNQueens(int n);

    void backtrack(std::vector<std::string> curr, int j, int n,
                   std::vector<bool> &columnUsage,
                   std::vector<std::vector<std::string>> &sol);

    bool isValidPlacement(int i, int j, int n, std::vector<std::string> curr);
};
