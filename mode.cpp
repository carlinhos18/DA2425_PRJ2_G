//
// Created by carlo on 26/03/2025.
//
#include "mode.h"
#include "read_files.cpp"
#include "mode_utils.cpp"

string getAlgorithm() {
    string Algorithm;
    while (true) {
        cout << "Algorithm <exhaustive/dynamic programming/approximation/integer linear programming/benchmark>: ";
        getline(cin, Algorithm);
        if (Algorithm == "exhaustive" || Algorithm == "dynamic programming" || Algorithm == "integer linear programming" || Algorithm == "approximation" || Algorithm == "benchmark") {
            return Algorithm;
        }
        cout << "Invalid mode! Please enter 'exhaustive', 'dynamic programming', 'approximation', 'integer linear programming' or 'benchmark'.\n";
    }
}

int getValidInteger(const string &prompt) {
    string input;
    int value;

    while (true) {
        cout << prompt;
        getline(std::cin, input);

        try {
            size_t pos;
            value = stoi(input, &pos);

            if (pos == input.size() && is_valid_integer(input)) {
                break;
            }
        } catch (...) {

        }

        cout << "Invalid input. Please enter a valid integer.\n";
    }

    return value;
}

InputData HandleUserInput() {
    InputData inputData;
    inputData.algorithm = getAlgorithm();

    if (inputData.algorithm == "benchmark") {
        return inputData;
    }

    int datasetNumber;
    while (true) {
        cout << "Choose a dataset number (1 to 10): ";
        string input;
        getline(cin, input);

        try {
            datasetNumber = stoi(input);
            if (datasetNumber >= 1 && datasetNumber <= 10) {
                break;
            } else {
                cout << "Please enter a number between 1 and 10.\n";
            }
        } catch (...) {
            cout << "Invalid input. Please enter a valid number.\n";
        }
    }

    const string prefix = "TruckAndPallets_";
    const string suffix = ".csv";

    stringstream ss;
    ss << prefix << std::setw(2) << std::setfill('0') << datasetNumber << suffix;
    string filename = ss.str();


    inputData.filename = filename;
    return inputData;
}

bool askSkipLongAlgorithms() {
    while (true) {
        cout << "Skip long-running algorithms (for instance, exhaustive for large datasets)? (yes/no): ";
        string input;
        getline(cin, input);

        transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input == "yes" || input == "y") {
            return true;
        } else if (input == "no" || input == "n") {
            return false;
        } else {
            cout << "Invalid input. Please type 'yes' or 'no'.\n";
        }
    }
}

