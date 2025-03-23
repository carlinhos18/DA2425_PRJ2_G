#include "read_files.cpp"
#include "apply.cpp"

Graph<Location>* map = new Graph<Location>();

unordered_map<string, Location> location_map; // maps the codes on the csv files

int main(){
    /*read_locations("./For Students/Locations.csv", location_map, map);
    read_distances("./For Students/Distances.csv", location_map, map);*/
    read_locations("./Example/Locations.csv", location_map, map);
    read_distances("./Example/Distances.csv", location_map, map);

    char choice;

    InputData inputData;

    cout << "Choose an input type:\n'f' for input.txt file; 'c' for manual write on the console" << endl;

    while (true) {
        cin >> choice;

        if (choice == 'f'){
            string filename = "input.txt";
            inputData = read_input_file(filename);

            if (!inputData.mode.empty()) {
                break;
            }

            cout << "File is not valid. Please confirm the structure and path of the file.\n";
            cout << "Correct Structure:\n";
            cout << "Mode:<walking/driving/driving-walking>\n";
            cout << "Source:<integer>\n";
            cout << "Destination:<integer>\n";
            cout << "(Optionals):\n";
            cout << "MaxWalkTime:<integer>\n";
            cout << "AvoidNodes:<integers, delimited by ','>\n";
            cout << "AvoidSegments:<list of (n1,n2), where n1 and n2 are integers and the pairs are delimited by ','>\n";
            cout << "IncludeNode:<integer>\n";

            cout << "Please enter 'f' or 'c'." << endl;

            cin.clear();
            cin.ignore();

        }else if (choice == 'c') {
            cin.clear();
            cin.ignore();

            string mode;

            while (true) {
                cout << "Mode <walking/driving/driving-walking>: ";
                getline(cin, mode);

                if (mode == "walking" || mode == "driving" || mode == "driving-walking") {
                    break;
                }
                cout << "Invalid mode! Please enter 'walking', 'driving', or 'driving-walking'." << endl;
            }

            int source = getValidInteger("Source <integer>: ");
            int destination = getValidInteger("Destination <integer>: ");

            cout << "Optionals - leave an empty field to skip any of them:\n";

            int MaxWalkTime = -1;
            if (mode != "driving") {
                string input;

                while (true) {
                    cout << "MaxWalkTime <integer>:";
                    getline(std::cin, input);

                    try {
                        if (input.empty()) {
                            MaxWalkTime = -1;
                            break;
                        }
                        size_t pos;
                        MaxWalkTime = stoi(input, &pos);

                        if (pos == input.size() && all_of(input.begin(), input.end(), ::isdigit)) {
                            break;
                        }
                    } catch (...) {

                    }

                    cout << "Invalid input. Please enter a valid integer.\n";
                }
            }

            unordered_set<int> avoidNodes;

            while (true) {
                cout << "AvoidNodes <integers, delimited by ','>: ";
                string avoidNodesInput;
                getline(cin, avoidNodesInput);

                if (avoidNodesInput.empty()) {
                    break;
                }

                stringstream ss(avoidNodesInput);
                string node;
                unordered_set<int> tempNodes;
                bool valid = true;

                while (getline(ss, node, ',')) {
                    try {
                        tempNodes.insert(stoi(node));
                    } catch (exception &e) {
                        cout << "Invalid input. Please enter a list of numbers separated by commas." << endl;
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    avoidNodes.insert(tempNodes.begin(), tempNodes.end());
                    break;
                }
            }

            vector<pair<int, int>> avoidSegments;

            while (true) {
                cout << "AvoidSegments <list of (n1,n2), where n1 and n2 are integers and the pairs are delimited by ','>: ";
                string avoidSegmentsInput;
                getline(cin, avoidSegmentsInput);

                if (avoidSegmentsInput.empty()) {
                    break;
                }

                stringstream ss(avoidSegmentsInput);
                string segment;
                vector<pair<int, int>> tempSegments;
                bool valid = true;

                while (getline(ss, segment, ')')) {
                    size_t openParen = segment.find('(');
                    size_t comma = segment.find(',');

                    if (openParen != string::npos && comma != string::npos && comma > openParen) {
                        try {
                            int n1 = stoi(segment.substr(openParen + 1, comma - openParen - 1));
                            int n2 = stoi(segment.substr(comma + 1));

                            tempSegments.emplace_back(n1, n2);
                        } catch (const exception&) {
                            cout << "Invalid input. Please enter pairs in the format (n1,n2) separated by ','." << endl;
                            valid = false;
                            break;
                        }
                    } else {
                        cout << "Invalid format. Please enter pairs in the format (n1,n2) separated by ','." << endl;
                        valid = false;
                        break;
                    }

                    if (ss.peek() == ',') {
                        ss.ignore();
                    }
                }

                if (valid) {
                    avoidSegments.insert(avoidSegments.end(), tempSegments.begin(), tempSegments.end());
                    break;
                }
            }

            int includeNode = -1;

            string input;
            while (true) {
                cout << "IncludeNode <integer>:";
                getline(std::cin, input);

                try {
                    if (input.empty()) {
                        includeNode = -1;
                        break;
                    }
                    size_t pos;
                    includeNode = stoi(input, &pos);

                    if (pos == input.size() && all_of(input.begin(), input.end(), ::isdigit)) {
                        break;
                    }
                } catch (...) {

                }

                cout << "Invalid input. Please enter a valid integer.\n";
            }


            inputData.mode = mode;
            inputData.source = source;
            inputData.destination = destination;
            inputData.MaxWalkTime = MaxWalkTime;
            inputData.avoidNodes = avoidNodes;
            inputData.avoidSegments = avoidSegments;
            inputData.includeNode = includeNode;

            break;
        }
        else {
            cout << "Invalid choice! Please enter 'f' or 'c'." << endl;

            cin.clear();
            cin.ignore();
        }
    }

    if (inputData.mode.empty()) {
        cerr << "Invalid Input Data. Ignoring" << endl;
        return 1;
    }

    displayInputData(inputData);

    OutputData outputData;
    //aplicar as funçoes ao grafo e adicionar a output data
    //saber que funçoes aplicar ao grafo conforme o input.
    apply_func(map, inputData, outputData);
    writeOutput(inputData, outputData);








    delete map;
    return 0;
}