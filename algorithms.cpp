#include <cstdint>
#include <random>
#include <algorithm>
using namespace std;

/**
 * 
 * @brief Calculates the total weight of all pallets in te output.  
 *
 * Iterates through the list of pallets in the output and sums their weights,
 * storing the result in output.totalWeight.
 * 
 * 
 * @param output The OutputData object that contains the pallets and
 * where the computed total weight will be stored.
 */

void weight_used(OutputData &output) {
    for (auto p : output.pallets) {
       output.totalWeight += p.weight;
    }
}


/**
 * @brief Exhaustive search algorithm for the knapsack problem.
 * 
 * This algorithm generates all possible combinations of pallets,
 * calculates their total weight and profit, and finds the best combination
 *
 * @param output The OutputData object where the result will be stored.
 *                - 'output.totalProfit' will contain the maximum profit found.
 *                - 'output.pallets' will contain the pallets that make up the best combination.
 * 
 * @param data The Algorithm object containing the pallets and total weight limit.
 *  
 */
void exhaustive(OutputData &output, Algorithm &data) {
    int n = data.pallets.size();
    int maxProfit = 0;
    vector<Pallet> bestCombination;
    vector<bool> usedItems(n, false);

    bool done = false;
    while (!done) {

        int weight = 0, profit = 0;
        vector<Pallet> current;

        for (int i = 0; i < n; ++i) {
            if (usedItems[i]) {
                weight += data.pallets[i].weight;
                profit += data.pallets[i].profit;
                if (weight > data.TotalWeight) break;
                current.push_back(data.pallets[i]);
            }
        }

        if (weight <= data.TotalWeight && profit > maxProfit) {
            maxProfit = profit;
            bestCombination = current;
        }

        int i = 0;
        while (i < n) {
            if (!usedItems[i]) {
                usedItems[i] = true;
                break;
            } else {
                usedItems[i] = false;
                ++i;
            }
        }
        if (i == n) done = true;
    }

    output.totalProfit = maxProfit;
    output.pallets = bestCombination;

}

/**
 *  @brief Dynamic Programming aproach.
 * 
 *  This algorithm uses the dynamic programming technique by selecting a subset of pallets that 
 *  that does not exeed the allowed limit ('data.TotalWeight'). It uses a bottom-up DP to build a table
 *  of maximum profits for each weight limit and number of pallets.
 * 
 * 
 * @param output The OutputData object where the result will be stored.
 *                - 'output.totalProfit' will contain the maximum profit found.
 *                - 'output.pallets' will contain the pallets that make up the best combination.
 * 
 * @param data The Algorithm object containing the pallets and total weight limit.
 *  
 */
void knapsackDP(OutputData &output, const Algorithm &data) {
    const int maxWeight = data.TotalWeight;
    const int n = data.pallets.size();

    vector<vector<int>> dp(n + 1, vector<int>(maxWeight + 1, 0));

    for (int i = 1; i <= n; ++i) {
        int w = data.pallets[i - 1].weight;
        int p = data.pallets[i - 1].profit;

        for (int j = 0; j <= maxWeight; ++j) {
            if (w <= j) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w] + p);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    int j = maxWeight;
    for (int i = n; i > 0; --i) {
        if (dp[i][j] != dp[i - 1][j]) {
            const Pallet &p = data.pallets[i - 1];
            output.pallets.push_back(p);
            output.totalProfit += p.profit;
            j -= p.weight;
        }
    }

    reverse(output.pallets.begin(), output.pallets.end());
}


/**
 * @brief Aproximation algorithm.
 * 
 * This function selects pallets to maximize total profit without exceeding the total weight limit (`data.TotalWeight`).
 * It uses a greedy heuristic that prioritizes pallets with the highest profit-to-weight ratio.
 * 
 * @param output The OutputData object where the result will be stored.
 *                - 'output.totalProfit' will contain the maximum profit found.
 *                - 'output.pallets' will contain the pallets that make up the best combination.
 * 
 * @param data The Algorithm object containing the pallets and total weight limit.
 *
 */
void knapsackGR_A(OutputData &output, const Algorithm &data) {
    const int maxWeight = data.TotalWeight;
    const int n = data.pallets.size();

    vector<pair<Pallet, double>> palletsRatio(n);

    for (unsigned int i = 0; i < n; i++) {
        palletsRatio[i] = {data.pallets[i], static_cast<double>(data.pallets[i].profit / data.pallets[i].weight)};
    }

    sort(palletsRatio.begin(), palletsRatio.end(), [](const pair<Pallet,double> &a, const pair<Pallet,double> &b) {
        return a.second > b.second;
    });

    unsigned int currentWeight = 0;

    for (unsigned int i = 0; i < n && currentWeight <= maxWeight; i++) {
        const Pallet cur_pallet = palletsRatio[i].first;
        if (currentWeight + cur_pallet.weight <= maxWeight) {
            output.pallets.push_back(cur_pallet);
            currentWeight += cur_pallet.weight;
            output.totalProfit += cur_pallet.profit;
        }
    }

}

/**
 * @brief Greedy algorithm 
 * 
 * This function selects pallets to maximize total profit without exceeding the total weight limit (`data.TotalWeight`).
 * It uses a greedy heuristic that prioritizes pallets with the highest **absolute profit**, regardless of weight.
 *  
 * @param output The OutputData object where the result will be stored.
 *                - 'output.totalProfit' will contain the maximum profit found.
 *                - 'output.pallets' will contain the pallets that make up the best combination.
 * 
 * @param data The Algorithm object containing the pallets and total weight limit.
 * 
 */
void knapsackGR_B(OutputData &output, const Algorithm &data) {
    const int maxWeight = data.TotalWeight;
    const int n = data.pallets.size();

    vector<pair<Pallet, double>> palletsRatio(n);

    for (unsigned int i = 0; i < n; i++) {
        palletsRatio[i] = {data.pallets[i], static_cast<double>(data.pallets[i].profit)};
    }

    sort(palletsRatio.begin(), palletsRatio.end(), [](const pair<Pallet,double> &a, const pair<Pallet,double> &b) {
        return a.second > b.second;
    });

    unsigned int currentWeight = 0;

    for (unsigned int i = 0; i < n && currentWeight <= maxWeight; i++) {
        const Pallet cur_pallet = palletsRatio[i].first;
        if (currentWeight + cur_pallet.weight <= maxWeight) {
            output.pallets.push_back(cur_pallet);
            currentWeight += cur_pallet.weight;
            output.totalProfit += cur_pallet.profit;
        }
    }
}

/**
 * 
 * @brief Aproximates a solution by comparing knapsackGR_A and knapsackGR_B.
 * 
 * This function evaluates two different greedy heuristics:
 * - `knapsackGR_A`: selects pallets based on highest profit-to-weight ratio.
 * - `knapsackGR_B`: selects pallets based on highest absolute profit.
 * 
 * It executes both strategies and chooses the one that yields the higher total profit.
 * 
 * @param output The OutputData object where the result will be stored.
 *                - 'output.totalProfit' will contain the maximum profit found.
 *                - 'output.pallets' will contain the pallets that make up the best combination.
 * 
 * @param data The Algorithm object containing the pallets and total weight limit. 
 * 
 */
void knapsackGR(OutputData &output, const Algorithm &data) {
    OutputData outputA;
    OutputData outputB;

    knapsackGR_A(outputA, data);
    knapsackGR_B(outputB, data);

    if (outputA.totalProfit >= outputB.totalProfit) {
        output = outputA;
    } else {
        output = outputB;
    }
}

/**
 * @brief Calculates the fitness of a chromosome.
 * 
 * This function evaluates a binary chromosome (vector of bools), where each element represents
 * wether a pallet is included (true) or not (false).
 * It computes the total profit and weight of the selected
 * pallets and returns the profit as the fitness value. If the total weight exceeds `maxWeight`, the fitness 
 * is penalized by returning 0.
 * 
 * @param chrom A vector of booleans representing the chromosome. Each element corresponds to a pallet.
 * @param data A constant reference to the Algorithm object containing:
 *             - `data.pallets`: vector of pallets with associated profit and weight.
 * @param maxWeight The maximum allowed weight for the selection.
 * 
 * @return The total profit of the selected pallets if the total weight is within the limit;
 *         otherwise, returns 0 as a penalty.
 * 
 */
int fitnessFunction(const vector<bool>& chrom, const Algorithm& data, const int maxWeight) {
    int profit = 0, weight = 0;
    for (int i = 0; i < static_cast<int>(chrom.size()); ++i) {
        if (chrom[i]) {
            profit += data.pallets[i].profit;
            weight += data.pallets[i].weight;
        }
    }
    return (weight > maxWeight) ? 0: profit; // Make the profit zero, to penalize Chromosomes with exceeding weight
}
/**
 * 
 * @brief Generates a random chromosome (candidate solution) for the problem.
 * 
 * This function creates a random binary chromosome representing a selection of pallets such that
 * the total weight does not exceed 'maxWeight'. Pallets are shuffled randomly, and then
 * added greedily until the weight limit is reached.
 * 
 * @param n The number of pallets (size of the chromosome).
 * @param maxWeight The maximum total allowed weight for the chromosome.
 * @param data Constant reference to an Algorithm object containing:
 *             - `data.pallets`: vector of pallets, each with weight and profit.
 * @param rng Reference to a Mersenne Twister random number generator for reproducibility.
 * 
 * @return A binary vector (chromosome) of size `n`, where each `true` indicates the corresponding pallet is selected.
 *  
 * 
 */
vector<bool> generateRandomChromosome(const int n, const int maxWeight, const Algorithm& data, mt19937& rng) {
    vector<bool> chrom(n, false);
    int totalWeight = 0;

    // Make a vector with the pallets indices and shuffle them
    vector<int> indices(n);
    iota(indices.begin(), indices.end(), 0);
    shuffle(indices.begin(), indices.end(), rng);

    // Try to add the pallets to the truck, until no more fit
    for (int i : indices) {
        int w = data.pallets[i].weight;
        if (totalWeight + w <= maxWeight) {
            chrom[i] = true;
            totalWeight += w;
        }
    }

    return chrom; // Return the candidate solution
}


/**
 * 
 * @brief Approximates a solution for the problem using a Genetic Algorithm(GA).
 * 
 * This function uses a population-based stochastic search to find a near-optimal set of pallets that maximizes 
 * total profit without exceeding the total weight limit. It simulates the process of natural selection through
 * reproduction, crossover, and mutation.
 * 
 * The genetic algorithm proceeds as follows:
 *  - Initialize a random population of valid chromosomes.
 *  - Evaluate each chromosome using a fitness function.
 *  - Select the best individuals as parents.
 *  - Generate offspring through crossover and mutation.
 *  - Repeat the process for a fixed number of generations.
 *  - Output the best solution found.
 *  
 * @param output The OutputData object where the result will be stored.
 *                - 'output.totalProfit' will contain the maximum profit found.
 *                - 'output.pallets' will contain the pallets that make up the best combination.
 * 
 * @param data The Algorithm object containing the pallets and total weight limit.
 *  
 * @note 
 *  - Uses fixed parameters: 200 generations, population size of 50, crossover rate 0.8, and mutation rate 0.05.
 *  - Ensures feasibility of chromosomes during initialization; infeasible offspring may arise during mutation.
 *    Penalization is applied via the fitness function (fitness = 0 if overweight).
 *  - The best two individuals from each generation are preserved to maintain elite solutions.
 * 
 * 
 */
void knapsackGA(OutputData &output, const Algorithm &data) {
    if (data.pallets.empty() || data.TotalWeight <= 0) return;

    const int maxWeight = data.TotalWeight;
    const int n = data.pallets.size();

    // These values can be changed
    const int generations = 200; // Number of cycles
    const int populationSize = 50; // Number of possible solutions in each generation
    const double crossoverRate = 0.8; // Chance that 2 solutions will "mix" into a new solution
    const double mutationRate = 0.05; // Chance that a bit in a solution will randomly flip (from 0 to 1 and vice versa)

    if (populationSize < 2 || n == 0) return;

    // RNG setup
    random_device rd; // Create a source of random data
    mt19937 rng(rd());  // Number Generator
    uniform_real_distribution<double> probDist(0.0, 1.0); // Random number between 0 and 1
    uniform_int_distribution<int> populationIndexDist(0, populationSize - 1); // Random number between 0 and the population size - 1 (Random population index)
    uniform_int_distribution<int> geneIndexDist(0, n - 1); // Random number between 0 and the number of genes (pallets) - 1 (Random pallet index in a candidate solution)

    using Chromosome = vector<bool>; // Each Chromosome (Candidate solution) is a vector that represents which pallets are included

    // Make the initial population
    vector<Chromosome> population(populationSize);
    for (auto& chrom : population) {
        chrom = generateRandomChromosome(n, maxWeight, data, rng);
    }

    // Track the best solution
    Chromosome bestChrom(n, false);
    int bestFitness = 0;

    for (int gen = 0; gen < generations; ++gen) {
        vector<pair<int, Chromosome>> evaluated;
        for (const auto &chrom : population) {
            int f = fitnessFunction(chrom, data, maxWeight);
            evaluated.emplace_back(f, chrom);

            if (f > bestFitness) {
                // Save the best solution so far
                bestFitness = f;
                bestChrom = chrom;
            }
        }

        sort(evaluated.begin(), evaluated.end(), greater<>());

        if (evaluated.size() < 2) continue;

        // Keep the 2 best solutions to be guaranteed to be kept on the next generation, so they're not lost to rng
        vector<Chromosome> newPopulation = {
            evaluated[0].second,
            evaluated[1].second
        };

        // Create a new generation
        while (newPopulation.size() < populationSize) {
            // Randomly pick 2 parents
            const Chromosome &parent1 = evaluated[populationIndexDist(rng)].second;
            const Chromosome &parent2 = evaluated[populationIndexDist(rng)].second;

            // Start with the child equal to one of the parents
            Chromosome child = parent1;

            // There's a chance that the child will be a combination of the 2 parents,
            // keeping the first 'point' (randomly generated value) pallets of the first, and the rest of the pallets be the same as the other parent
            if (probDist(rng) < crossoverRate) {
                int point = geneIndexDist(rng);
                for (int i = point; i < n; ++i) {
                    child[i] = parent2[i];
                }
            }

            // Apply the mutation chance
            for (int i = 0; i < n; ++i) {
                if (probDist(rng) < mutationRate) {
                    child[i] = !child[i];
                }
            }

            newPopulation.push_back(child); // Add the new chromosome to the next generation
        }

        population = newPopulation; // Start treating the new generation
    }

    // Compute the final solution's value, adding the used pallets to the output
    for (int i = 0; i < n; ++i) {
        if (bestChrom[i]) {
            const Pallet &p = data.pallets[i];
            output.pallets.push_back(p);
            output.totalProfit += p.profit;
        }
    }
}
