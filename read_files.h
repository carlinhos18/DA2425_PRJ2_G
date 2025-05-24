//
// Created by carlo on 26/03/2025.
//

#ifndef READ_FILES_H
#define READ_FILES_H

#include "data_structures/structures.h"
#include <vector>
#include <string>
using namespace std;

/**
 * 
 * @brief Reads the truck data from a CSV file and loads it into the provided Algoritm structure.
 * 
 * This function opens a truck data file, parses its content to retrieve the truck's capacity
 * and number of pallets, and sets the `TotalWeight` in the `Algorithm` object. It also determines
 * the corresponding pallets file based on the truck ID and reads its data.
 * 
 * The filename should be in the format "TruckAndPallets_ID.csv", where ID is the truck identifier.
 * The pallets file should be named "Pallets_ID.csv" where ID matches the truck ID.
 * 
 * @param filename The name of the truck data file to read.
 * @param data The `Algorithm` structure where the truck and pallets data will be stored.
 * 
 * @throws std::runtime_error If the file cannot be opened or if the file format is incorrect.
 */
void read_truck_file(const string& filename, Algorithm& data);


/**
 * 
 * @brief Reads the pallets data from a CSV file and loads it into the provided Algorithm structure.
 * 
 * This function opens a pallets data file, parses its content to retrieve each pallet's ID, weight,
 * and profit, and stores them in the `pallets` vector of the `Algorithm` object.
 * 
 * The filename should be in the format "Pallets_ID.csv", where ID corresponds to the truck ID.
 * 
 * @param filename The name of the pallets data file to read.
 * @param data The `Algorithm` structure where the pallets data will be stored.
 * 
 * @throws std::runtime_error If the file cannot be opened or if the file format is incorrect.
 */
void read_pallets_file(const string& filename, Algorithm& data);



#endif //READ_FILES_H
