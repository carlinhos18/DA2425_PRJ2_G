//
// Created by carlo on 11/04/2025.
//
#include <fstream>
#include "data_structures/structures.h"
#include "algorithms.cpp"
#include <chrono>
using namespace std;


/**
 * 
 * @brief Applies the selected algorithm (user choosen) and to the choosen dataset.
 * 
 *  This function reads the input data, applies the specified algorithm to the specified dataset,
 *  and updates the output data with the results.
 * 
 * 
 * @param output The output data structure to store the results of the algorithm.
 * @param data The algorithm data structure containing the pallets and total weight.
 * @param input The input data structure containing the algorithm name and filename.
 */
void apply(OutputData &output, Algorithm &data, const InputData& input){
    const string algorithm = input.algorithm;

    if (algorithm == "exhaustive") {
        exhaustive(output, data);
    }
    if (algorithm == "dynamic programming") {
        knapsackDP(output, data);
    }
    if (algorithm == "approximation") {
        knapsackGR(output, data);
    }
    if (algorithm == "genetic") {
        knapsackGA(output, data);
    }

    weight_used(output);
}

#include <fstream>
#include <iomanip>  // for std::fixed and std::setprecision

/**
 * 
 * @brief Benchmarks the performance of different algorithms on a series of datasets.
 * 
 * 
 ** This function loads multiple dataset files, each representing a truck's pallet configuration,
 * and applies different knapsack-solving algorithms to each. It measures and records the execution time
 * for each algorithm and outputs the results both to the console and a file named `"benchmark_test.txt"`.
 * 
 * The algorithms benchmarked are:
 * - `"exhaustive"`: Brute-force approach (may be skipped for larger datasets).
 * - `"dynamic programming"`: Optimal DP-based solution.
 * - `"approximation"`: Greedy heuristic (hybrid of profit-to-weight ratio and raw profit).
 * - `"genetic"`: Genetic Algorithm for approximating solutions.
 * 
 * The benchmarking process involves:
 *  - Iterating through 10 predefined input files (named `TruckAndPallets_01.csv` to `TruckAndPallets_10.csv`).
 *  - Applying each algorithm to the dataset.
 *  - Timing each algorithm using `std::chrono`.
 *  - Optionally skipping the exhaustive algorithm on medium-size datasets if `skipLong` is true.
 * 
 *  @param skipLong if tru, the exhaustive algorithm will be skipped for datasets 4, 5, and 6 to avoid long execution times.
 * 
 * @note
 * The function writes benchmark results to a file named `benchmark_test.txt`, overwriting any previous content.
 * Time is reported in microseconds for fast algorithms and seconds for slower ones.
 * 
 * 
 * 
 */
void benchmarkMode(bool skipLong) {
    std::ofstream outfile("benchmark_test.txt");

    for (int i = 1; i <= 10; i++) {
        const string prefix = "TruckAndPallets_";
        const string suffix = ".csv";

        stringstream ss;
        ss << prefix << setw(2) << setfill('0') << i << suffix;
        string dataset = ss.str();

        Algorithm data;
        read_truck_file(dataset, data);
        int numPallets = data.pallets.size();

        // Output header
        cout << "File: " << dataset << " - Pallets: " << numPallets << "\n";
        outfile << "File: " << dataset << " - Pallets: " << numPallets << "\n";
        cout << "----Times----\n";
        outfile << "----Times----\n";

        vector<string> algorithms = {
            "exhaustive",
            "dynamic programming",
            "approximation",
            "genetic"
        };

        for (const auto& algorithm_name : algorithms) {
            if (skipLong && algorithm_name == "exhaustive" && (i == 4 || i == 5 || i == 6)) {
                cout << algorithm_name << ": skipped\n";
                outfile << algorithm_name << ": skipped\n";
                continue;
            }

            OutputData output;
            InputData inputData;
            inputData.filename = dataset;
            inputData.algorithm = algorithm_name;

            auto start = chrono::high_resolution_clock::now();

            if (algorithm_name == "exhaustive") {
                exhaustive(output, data);
            } else if (algorithm_name == "dynamic programming") {
                knapsackDP(output, data);
            } else if (algorithm_name == "approximation") {
                knapsackGR(output, data);
            } else if (algorithm_name == "genetic") {
                knapsackGA(output, data);
            }

            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            long long microseconds = duration.count();

            string label = algorithm_name;
            if (label == "dynamic programming") label = "Dynamic Programming";
            else if (label == "approximation") label = "Approximation";
            else if (label == "genetic") label = "Genetic";
            else label = "Exhaustive";

            cout << label << ": ";

            outfile << label << ": ";
            if (microseconds >= 62500) {
                double seconds = microseconds / 1'000'000.0;
                outfile << std::fixed << std::setprecision(6) << seconds << " s\n";
                cout << std::fixed << std::setprecision(6) << seconds << " s\n";
            } else {
                outfile << microseconds << " µs\n";
                cout << microseconds << " microseconds\n";
            }
        }

        cout << "\n";
        outfile << "\n";
    }

    outfile.close();
}

