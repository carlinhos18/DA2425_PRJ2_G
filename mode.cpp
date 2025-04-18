//
// Created by carlo on 26/03/2025.
//
#include "mode.h"
#include "read_files.cpp"
#include "mode_utils.cpp"

string getAlgorithm() {
    string Algorithm;
    while (true) {
        cout << "Algorithm <exhaustive/dynamic programming/approximation/integer linear programming>: ";
        getline(cin, Algorithm);
        if (Algorithm == "exhaustive" || Algorithm == "dynamic programming" || Algorithm == "integer linear programming" || Algorithm == "approximation") {
            return Algorithm;
        }
        cout << "Invalid mode! Please enter 'exhaustive', 'dynamic programming', 'approximation' or 'integer linear programming'.\n";
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
    string filename;
    const string prefix = "TruckAndPallets_";
    const string suffix = ".csv";

    while (true) {
        cout << "Enter filename (format: TruckAndPallets_<X>.csv): ";
        getline(cin, filename);

        bool valid = isFileValid(filename, prefix, suffix);

        string id_part = filename.substr(prefix.size(), filename.size() - prefix.size() - suffix.size());

        if (valid && !id_part.empty()) {
                inputData.filename = filename;
                return inputData;
        }
        cout << "Invalid filename format. Expected: TruckAndPallets_<X>.csv\n";
    }
}