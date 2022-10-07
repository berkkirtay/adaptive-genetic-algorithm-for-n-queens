#include "BacktrackingAlgorithm.h"

std::vector<std::vector<std::string>> BacktrackingAlgorithm::solveNQueens(int n)
{
    std::vector<std::string> curr;
    std::vector<bool> columnUsage(n, false);
    for (int i = 0; i < n; i++)
    {
        std::string row = "";
        for (int j = 0; j < n; j++)
        {
            row += '.';
        }
        curr.push_back(row);
    }
    std::vector<std::vector<std::string>> sol;
    backtrack(curr, 0, n, columnUsage, sol);
    return sol;
}

void BacktrackingAlgorithm::backtrack(std::vector<std::string> curr,
                                      int j, int n, std::vector<bool> &columnUsage,
                                      std::vector<std::vector<std::string>> &sol)
{
    if (j >= n)
    {
        sol.push_back(curr);
        if (sc.checkSolution(curr))
        {
            for (auto &str : curr)
            {
                std::cout << str << std::endl;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (columnUsage[i] == false && isValidPlacement(i, j, n, curr))
        {
            curr[j][i] = 'Q';
            columnUsage[i] = true;
            backtrack(curr, j + 1, n, columnUsage, sol);
            curr[j][i] = '.';
            columnUsage[i] = false;
        }
    }
}

bool BacktrackingAlgorithm::isValidPlacement(int i, int j, int n, std::vector<std::string> curr)
{
    int x = 0;
    int y = 0;
    while (x < n)
    {
        if (curr[x++][i] == 'Q')
        {
            return false;
        }
    }

    x = j - 1;
    y = i - 1;
    while (x >= 0 && y >= 0)
    {
        if (curr[x][y] == 'Q')
        {
            return false;
        }
        x--;
        y--;
    }

    x = j - 1;
    y = i + 1;
    while (x >= 0 && y < n)
    {
        if (curr[x][y] == 'Q')
        {
            return false;
        }
        x--;
        y++;
    }
    return true;
}