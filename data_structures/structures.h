//
// Created by carlo on 22/03/2025.
//

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <vector>

struct Pallet{
    int id;
    int weight;
    int profit;
};

struct Truck{
    int capacity;
    int n_pallets;
    std::string truck_id;
};

struct InputData{
    std::string algorithm;
    std::string filename;
};

struct OutputData{
    int totalProfit;
    int totalWeight;
    std::vector<Pallet> pallets;
};

#endif //STRUCTURES_H

