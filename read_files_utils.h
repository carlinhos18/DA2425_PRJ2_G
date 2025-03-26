//
// Created by ceraizi on 26-03-2025.
//

#ifndef READ_FILES_UTILS_H
#define READ_FILES_UTILS_H

#include <sstream>
#include <fstream>
#include <iostream>
#include "data_structures/Structures.h"
#include <unordered_map>

/* Union between two Vertexes */
void add_edge(const Distance& info, unordered_map<string, Location>& location_map, Graph<Location>* map);

/* Check if number in file is valid */
bool is_valid_integer(const string& str);

#endif //READ_FILES_UTILS_H
