//
// Created by carlo on 13/04/2025.
//

#include <iostream>
#include "data_structures/structures.h"

void write_output(OutputData &output, Algorithm &data) {
    cout << "Pallets used: \n \n";
    for (auto pallet: output.pallets) {
        cout << "Pallet: " << pallet.id << endl <<
        "Weight: " <<  pallet.weight << endl <<
        "Profit: " << pallet.profit << "\n \n";
    }
    cout << "Initial Weight available: " << data.TotalWeight << endl;
    cout << "Total Weight Used: " << output.totalWeight << "\n \n";
    cout << "Total Profit: " << output.totalProfit << endl;
}