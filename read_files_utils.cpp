//
// Created by ceraizi on 26-03-2025.
//
#include "read_files_utils.h"

bool is_valid_integer(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

#include <string>
#include <iostream>

string get_truck_id(const string& filename) {
    size_t underscore_pos = filename.rfind('_');
    size_t dot_pos = filename.rfind('.');

    if (underscore_pos != string::npos && dot_pos != string::npos && dot_pos > underscore_pos) {
        string id = filename.substr(underscore_pos + 1, dot_pos - underscore_pos - 1);
        return id;
    } else {
        return "";
    }
}
