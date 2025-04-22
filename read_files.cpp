#include "read_files.h"
#include "read_files_utils.cpp"
#include <fstream>


void read_truck_file(const string& filename, Algorithm& data) {
    string correct = "Datasets_Project2/datasets/" + filename;
    cout <<"TruckFileDirectory: " << correct << endl;
    ifstream infile(correct);
    string line;

    if (!infile.is_open()) {
        cerr << "Could not open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    getline(infile, line); // Ignorar cabeçalho

    if (!getline(infile, line)) {
        cerr << "Erro: Ficheiro não tem dados após o cabeçalho!" << endl;
        exit(EXIT_FAILURE);
    }

    stringstream ss(line);
    string capacity_str, n_pallets_str;
    getline(ss, capacity_str, ',');
    getline(ss, n_pallets_str, ',');

    Truck truck;
    truck.capacity = stoi(capacity_str);
    data.TotalWeight = truck.capacity;
    truck.n_pallets = stoi(n_pallets_str);
    truck.truck_id = get_truck_id(filename);

    string pallets_file = "Pallets_" + truck.truck_id + ".csv";
    read_pallets_file(pallets_file, data);

    infile.close();
}


void read_pallets_file(const string& filename, Algorithm& data){
    string correct = "Datasets_Project2/datasets/" + filename;
    cout << "PalletsFileDirectory: " << correct << endl;
    ifstream infile(correct);
    string line;

    if (!infile.is_open()) {
        cerr << "Could not open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    getline(infile, line); // Ignorar cabeçalho

    while (getline(infile, line)) {
        stringstream ss(line);
        Pallet pallet;
        string idStr, weightStr, profitStr;

        getline(ss, idStr, ',');
        getline(ss, weightStr, ',');
        getline(ss, profitStr, ',');

        pallet.id = stoi(idStr);
        pallet.weight = stoi(weightStr);
        pallet.profit = stoi(profitStr);

        data.pallets.push_back(pallet);
    }

    infile.close();
}



