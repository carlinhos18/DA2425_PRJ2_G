#include "mode.cpp"
#include <iostream>

using namespace std;

int main() {
    InputData inputData = HandleUserInput();
    //now we call the map_Function to apply the correct algorithm that the user chose to the file

    Algorithm data;
    read_truck_file(inputData.filename, data);
    for (auto p : data.pallets) {
        cout << "Id: " << p.id << " "
        << "Weight: " << p.weight << " "
        << "Profit: " << p.profit << "\n";
    }
    cout << "Total Weight: " << data.TotalWeight << endl;


    return 0;
}
