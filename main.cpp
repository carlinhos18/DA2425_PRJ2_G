#include "read_files.cpp"
#include "algorithms.cpp"
Graph<Location>* map = new Graph<Location>();

unordered_map<string, Location> location_map; // maps the codes on the csv files

int main(){
    read_locations("./For Students/Locations.csv", location_map, map);
    read_distances("./For Students/Distances.csv", location_map, map);


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

            cout << "Please enter 'f' or 'c'." << endl;

            cin.clear();
            cin.ignore();

        }else if (choice == 'c') {
            cin.clear();
            cin.ignore();

            string mode;

            while (true) {
                cout << "Mode (walking, driving, driving-walking): ";
                getline(cin, mode);

                if (mode == "walking" || mode == "driving" || mode == "driving-walking") {
                    break;
                }
                cout << "Invalid mode! Please enter 'walking', 'driving', or 'driving-walking'." << endl;
            }

            int source = getValidInteger("Source: ");
            int destination = getValidInteger("Destination: ");

            inputData.source = source;
            inputData.destination = destination;
            inputData.mode = mode;

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






    delete map;
    return 0;
}