#include "FitnessChecker.h"

int FitnessChecker::calculateFitnessFunction(std::vector<std::string> solution)
{
    int penalty = 0;
    int size = static_cast<int>(solution.size());
    std::vector<bool> columnUsage(size, false);
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size; i++)
        {
            if (solution[j][i] == 'Q')
            {
                if (columnUsage[i] == false &&
                    isAValidPlacement(i, j, size, solution) == true)
                {
                    columnUsage[i] = true;
                }
                else
                {
                    penalty++;
                }
            }
        }
    }
    return solution.size() - penalty;
}

bool FitnessChecker::isAValidPlacement(int i, int j, int n,
                                       std::vector<std::string> curr)
{
    int x = 0;
    int y = 0;
    while (x < n)
    {
        if (j != x && curr[x][i] == 'Q')
        {
            return false;
        }
        x++;
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