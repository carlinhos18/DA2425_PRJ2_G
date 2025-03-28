//
// Created by ceraizi on 26-03-2025.
//
#include "read_files_utils.h"

void add_edge(const Distance& info, unordered_map<string, Location>& location_map, Graph<Location>* map) {
    const auto it1 = location_map.find(info.start_node);
    const auto it2 = location_map.find(info.dest_node);

    if (it1 == location_map.end() || it2 == location_map.end()) {
        cerr << "Could not add edge between " << info.start_node << " and "
        << info.dest_node << endl;
        exit(EXIT_FAILURE);
    }
    Location loc1 = it1->second;
    Location loc2 = it2->second;
    map->addBidirectionalEdge(loc1, loc2, info.drive_dist, info.walk_dist);
}


bool is_valid_integer(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}