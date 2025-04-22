//
// Created by carlo on 13/04/2025.
//

#include <iostream>
#include "data_structures/structures.h"

void write_output(OutputData &output) {
    int Weight_Used = 0;
    cout << "Pallets used: \n \n";
    for (auto pallet: output.pallets) {
        cout << "Pallet: " << pallet.id << endl <<
        "Weight: " <<  pallet.weight << endl <<
        "Profit: " << pallet.profit << "\n \n";
        Weight_Used += pallet.weight;
    }

    cout << "Total Weight Used: " << Weight_Used << "\n \n";
    cout << "Total Profit: " << output.totalProfit << endl;
}