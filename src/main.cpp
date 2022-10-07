#include <vector>
#include <iostream>
#include "Backtrackingalgorithm.h"
#include "GeneticAlgorithm.h"

using namespace std;

int main()
{
  // BacktrackingAlgorithm backtrackingAlgorithm;
  //  backtrackingAlgorithm.solveNQueens(10);

  GeneticAlgorithm ga(13, 100);
  ga.process();
  return 0;
}