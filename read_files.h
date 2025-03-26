//
// Created by carlo on 26/03/2025.
//

#ifndef READ_FILES_H
#define READ_FILES_H

#include "data_structures/Structures.h"
#include <unordered_map>

/* Creates Vertexes */
void read_locations(const string& filename, unordered_map<string, Location>& location_map, Graph<Location>* map);

/* Union between two Vertexes */
void add_edge(const Distance& info, unordered_map<string, Location>& location_map, Graph<Location>* map);

/* Creates Edges and adds them */
void read_distances(const string& filename, unordered_map<string, Location>& location_map, Graph<Location>* map);

/* Check if number in file is valid */
bool is_valid_integer(const string& str);

/* If valid number gets it */
int getValidInteger(const string &prompt);

/* Reads file */
InputData read_input_file(const string& filename);

/* Writes output to file and displays it on terminal */
void writeOutput(const InputData& inputData, const OutputData& outputData);


#endif //READ_FILES_H
