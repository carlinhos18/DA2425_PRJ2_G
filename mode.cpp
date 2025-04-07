//
// Created by carlo on 26/03/2025.
//
#include "mode.h"
#include "read_files.cpp"

string getMode() {
    string mode;
    while (true) {
        cout << "Mode <driving/driving-walking>: ";
        getline(cin, mode);
        if (mode == "driving" || mode == "driving-walking") {
            return mode;
        }
        cout << "Invalid mode! Please enter 'driving' or 'driving-walking'.\n";
    }
}

unordered_set<int> getAvoidNodes() {
    unordered_set<int> avoidNodes;
    cout << "AvoidNodes <n1,n2,...> (optional): \n";
    string input;
    getline(cin, input);
    stringstream ss(input);
    string node;
    while (getline(ss, node, ',')) {
        try {
            avoidNodes.insert(stoi(node));
        } catch (...) {
            cout << "Invalid input. Please enter numbers separated by commas.\n";
            return getAvoidNodes();
        }
    }
    return avoidNodes;
}

vector<pair<int, int>> getAvoidSegments() {
    vector<pair<int, int>> avoidSegments;
    cout << "AvoidSegments <(n1,n2),(n3,n4)> (optional): \n";
    string input;
    getline(cin, input);
    stringstream ss(input);
    string segment;
    while (getline(ss, segment, ')')) {
        size_t openParen = segment.find('(');
        size_t comma = segment.find(',');
        if (openParen != string::npos && comma != string::npos && comma > openParen) {
            try {
                int n1 = stoi(segment.substr(openParen + 1, comma - openParen - 1));
                int n2 = stoi(segment.substr(comma + 1));
                avoidSegments.emplace_back(n1, n2);
            } catch (...) {
                cout << "Invalid format! Use (n1,n2) separated by commas.\n";
                return getAvoidSegments();
            }
        }
        if (ss.peek() == ',') ss.ignore();
    }
    return avoidSegments;
}

int getIncludeNode() {
    string input;
    cout << "Include node <int> (optional): ";
    getline(cin, input);

    if (input.empty()) {
        return -1;
    }

    if (is_valid_integer(input)) {
        return stoi(input);
    }
    cout << "Invalid input! Please enter a valid integer.\n";
    return getIncludeNode();

}
int getMaxWalk() {
    string input;
    cout << "MaxWalkTime <int>: ";
    getline(cin, input);

    if (input.empty()) {
        cout << "MaxWalkTime is mandatory \n";
        return getMaxWalk();
    }

    if (is_valid_integer(input)) {
        return stoi(input);
    }

    cout << "Invalid input! Please enter a valid integer.\n";
    return getMaxWalk();
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
    char choice;

    while (true) {
        cout << "Enter 'f' to read from file or 'c' to input manually: \n";
        cin >> choice;
        cin.ignore();

        if (choice == 'f') {
            string filename = "input.txt";
            inputData = read_input_file(filename);
            if (!inputData.mode.empty()) {
                return inputData;
            }
            cout << "File is not valid. Please confirm the structure and path.\n";
        } else if (choice == 'c') {
            inputData.mode = getMode();
            inputData.source = getValidInteger("Source <int>: ");
            inputData.destination = getValidInteger("Destination <int>: ");
            if (inputData.mode != "driving") {
                inputData.MaxWalkTime = getMaxWalk();
            }
            inputData.avoidNodes = getAvoidNodes();
            inputData.avoidSegments = getAvoidSegments();
            if (inputData.mode == "driving") {
                inputData.includeNode = getIncludeNode();
            }
            return inputData;
        } else {
            cout << "Invalid choice! Please enter 'f' or 'c'.\n";
        }
    }
}
