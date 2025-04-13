//
// Created by carlo on 22/03/2025.
//

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <vector>

struct Pallet{
    int id = 0;
    int weight = 0;
    int profit = 0;
};

struct Truck{
    int capacity = 0;
    int n_pallets = 0;
    std::string truck_id;
};

struct InputData{
    std::string algorithm;
    std::string filename;
};

struct Algorithm {
    std::vector<Pallet> pallets = {};
    int TotalWeight = 0;
};

struct OutputData{
    int totalProfit = 0;
    int totalWeight = 0;
    std::vector<Pallet> pallets = {};
};

#endif //STRUCTURES_H

