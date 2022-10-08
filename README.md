# An Adaptive Genetic Algorithm for N-Queens problem
[![C++ Build CI](https://github.com/berkkirtay/adaptive-genetic-algorithm-for-n-queens/actions/workflows/main.yml/badge.svg?branch=main)](https://github.com/berkkirtay/adaptive-genetic-algorithm-for-n-queens/actions/workflows/main.yml)

**I implemented a genetic algorithm for the N-Queens problem with several improvements. 
This implementation can be a reference point for further developments or a helper to implement 
algorithms for harder NP problems. GA code is written in C++.** 

**To improve the algorithm, a tuner must be developed for different input sizes. For example, 
the algorithm can find a optimal solution in a neglible time for N=35 but can get stuck at a local optimum for N=36. This
issue can be overcome by developing a good tuner for the algorithm parametes.** 

**Currently, the algorithm has ordinary components of GA. In addition to these, 
it has a static adaptation feature. A dynamic adaptation(self-adaptation) algorithm 
would be developed if the problem had dynamic constraints and parameters.**

## Components:
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
Mutation is simply done by swapping genes of a individual.

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
    return survivors;
```

### Tuner
Currently, I created a tuning csv file for different size of inputs. In the future, I will
develop a tuner by using the data in that file.

## Results:

| TableSize(N) | PopSize | ParentSelectionPressure | SurvivorSelectionPressure | MutationPressure | ExecutionTime |
| :---:        | :---:   | :---:                   |  :---:                    |  :---:           |  :---:        |
| 20           | 120     | 0.2                     |   0.5                     |   1.2            |  1s           |
| 21           | 147     | 0.2                     |   0.5                     |   1.2            |  3s           |
| 30           | 510     | 1                       |   0.5                     |   2              |  22s          |
| 37           | 296     | 1                       |   0.5                     |   2              |  114s         |

## Usage:
build/run.sh script will run the algorithm after compilation.

## 
## TODO: 
- Implement a tuning algorithm for GA
