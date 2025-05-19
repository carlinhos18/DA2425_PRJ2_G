//
// Created by carlo on 11/04/2025.
//
#include "data_structures/structures.h"
#include "algorithms.cpp"
#include <chrono>
using namespace std;

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
    if (algorithm == "integer linear programming") {

    }

    weight_used(output);
}

void benchmarkMode(bool skipLong) {
    for (int i = 1; i <= 10; i++) {
        const string prefix = "TruckAndPallets_";
        const string suffix = ".csv";

        stringstream ss;
        ss << prefix << setw(2) << setfill('0') << i << suffix;
        string dataset = ss.str();

        cout << "Running benchmark for dataset: " << dataset << endl;

        Algorithm data;
        read_truck_file(dataset, data);

        vector<string> algorithms = {
            "exhaustive",
            "dynamic programming",
            "approximation"
        };

        for (const auto& algorithm_name : algorithms) {
            if (skipLong && algorithm_name == "exhaustive" && (i == 4 || i == 5 || i == 6)) {
                cout << "Skipping " << algorithm_name << " for dataset " << dataset << " due to expected long runtime.\n";
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
            }


            auto end = chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<chrono::microseconds>(end - start);
            std::cout << "Algorithm " << algorithm_name << " took "
                      << duration.count() << " microseconds." << std::endl;
        }
    }
}