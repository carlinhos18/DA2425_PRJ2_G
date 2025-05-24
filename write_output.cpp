//
// Created by carlo on 13/04/2025.
//

#include <iostream>
#include "data_structures/structures.h"


/**
 * 
  * @brief Prints the details of the selected pallets, total weight used, and total profit.
 * 
 * This function outputs to the console the list of pallets included in the solution,
 * displaying each pallet's ID, weight, and profit. It also prints the initial available
 * weight capacity of the truck, the total weight used by the selected pallets, and
 * the total profit achieved.
 * 
 * @param output The OutputData object containing the selected pallets and their total weight and profit.
 * @param data The Algorithm object containing the initial total weight capacity.
 * 
 */
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