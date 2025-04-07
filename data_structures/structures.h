//
// Created by carlo on 22/03/2025.
//

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

struct Pallet{
    int id;
    int weight;
    int profit;
};

struct Truck{
  int capacity;
  int n_pallets;
  string truck_id;
};

struct InputData{
    string algorithm;
    string filename;
};

struct OutputData{
    int totalProfit;
    int totalWeight;
    vector<Pallet> pallets;
};

#endif //STRUCTURES_H

