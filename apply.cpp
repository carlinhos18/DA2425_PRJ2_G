//
// Created by carlo on 11/04/2025.
//
#include <fstream>
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
    if (algorithm == "genetic") {
        knapsackGA(output, data);
    }

    weight_used(output);
}

#include <fstream>
#include <iomanip>  // for std::fixed and std::setprecision

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
        cout << "Times:\n";
        outfile << "Times:\n";

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

            cout << label << ": " << microseconds << "\n";

            outfile << label << ": ";
            if (microseconds >= 62500) {
                double seconds = microseconds / 1'000'000.0;
                outfile << std::fixed << std::setprecision(6) << seconds << " s\n";
            } else {
                outfile << microseconds << " µs\n";
            }
        }

        cout << "\n";
        outfile << "\n";
    }

    outfile.close();
}

