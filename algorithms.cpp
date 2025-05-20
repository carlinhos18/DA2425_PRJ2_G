#include <cstdint>
#include <random>
#include <algorithm>
using namespace std;
//
// Created by carlo on 13/04/2025.
//
void weight_used(OutputData &output) {
    for (auto p : output.pallets) {
       output.totalWeight += p.weight;
    }
}

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

// Function that returns how good a Chromosome / candidate solution is - It's profit
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
