//
// Created by carlo on 26/03/2025.
//

#ifndef READ_FILES_H
#define READ_FILES_H

#include "data_structures/structures.h"
#include <vector>
#include <string>
using namespace std;

void read_truck_file(const string& filename, vector<Pallet>* pallets);

void read_pallets_file(const string& filename, vector<Pallet>* pallets);



#endif //READ_FILES_H
