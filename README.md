# An Adaptive Genetic Algorithm for N-Queens problem
[![C++ Build CI](https://github.com/berkkirtay/adaptive-genetic-algorithm-for-n-queens/actions/workflows/main.yml/badge.svg?branch=main)](https://github.com/berkkirtay/adaptive-genetic-algorithm-for-n-queens/actions/workflows/main.yml)

**I implemented a genetic algorithm for the N-Queens problem with several improvements. 
This implementation can be a reference point for further developments or a helper to implement 
algorithms for harder NP problems. GA code is written in C++.** 

**To improve the algorithm, a tuner must be developed for different input sizes. For example, 
the algorithm can find a optimal solution in a negligible time time for N=35 but can get stuck at a local optimum for N=36. This
issue can be overcome by developing a good tuner for the algorithm parameters.** 

**Currently, the algorithm has ordinary components of GA. In addition to these, 
it has a static adaptation feature. Moreover, a dynamic adaptation(self-adaptation) algorithm 
would be developed if the problem had dynamic constraints and parameters.**

## Components:

### Representation (Genetics)
An individuals(chromosome) genetics is constructed by permutations. For example, for a N=4 table,
a sample individual may have the following sequence:

**2413** which represents the following table:
```
-Q--
---Q
Q---
--Q-
```

### Selection
The algorithm consists of the following selection mechanisms:
  - Random Parent Selection
  - Tournament Parent Selection
  - Crowding Survivor Selection
  - Random Survivor Selection
  - Elitist Survivor Selection (currently not used)

### Recombination
The algorithm uses crossover operation to generate new individuals:

Crossover types:
  - Cut And Crossfill Crossover
  - Uniform Crossover

### Mutation
Mutation is simply done by swapping genes of an individual.

### Fitness Function
Individuals fitness scores are calculated by counting how many queens check each other.
For example, for a N=15 individual if 5 queens check each other then its fitness score 
will be 10 by the following equation: 

`Fitness = N - queen checks`

### Adaptation 
In every new generation, a population variance is calculated and adaptation 
algorithm makes decisions between different approaches based on the population variance.
The algorithm will check selection and mutation pressure to make the decisions.
For example, if the population variance is 1 and mutation pressure 1.5, algorithm will make the
decision of mutating by the following statement:

`population variance < mutation pressure`

The algorithm also checks for parent and survivor selections. This provides a solution
to the problem of over selection. Usually, the adaptation algorithm balances the system with 
two basic search behaviors: **Exploration and exploitation**.

The following code block explains this approach for survival selection:
```cpp
if (populationVariance < survivalSelectionPressure)
{
    // Exploration
    survivors = randomSurvivorSelection(parents, children);
}
else
{
    // Exploitation
    survivors = crowdingSurvivalSelection(parents, children);
}
```

### Tuner
Currently, I created a tuning csv file for different size of inputs. In the future, I will
develop a tuner by using the data in that file.

## Results:

| TableSize(N) | PopSize | ParentSelectionPressure | SurvivorSelectionPressure | MutationPressure | ExecutionTime |
| :---:        | :---:   | :---:                   |  :---:                    |  :---:           |  :---:        |
| 20           | 120     | 0.2                     |   0.5                     |   1.2            |  0.2s         |
| 21           | 147     | 0.2                     |   0.5                     |   1.2            |  0.3s         |
| 25           | 250     | 2                       |   3                       |   10             |  0.2s         |
| 30           | 510     | 1                       |   0.5                     |   2              |  2.2s         |
| 40           | 400     | 2                       |   3                       |   10             |  1.7s         |
| 50           | 500     | 2                       |   3                       |   10             |  5.3s         |

## Usage:
build/run.sh script will run the algorithm after compilation.

The script must run with specified arguments. An example may be like:

**$ ./run.sh -t 20 -p 200 -pp 2 -sp 1 -mp 5**

## Test Run Example:


## References:
[1]	Eiben, A. and Smith, J., 2015. Introduction to Evolutionary Computing. 2nd ed. Berlin: Springer.
