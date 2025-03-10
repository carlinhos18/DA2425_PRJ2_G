#include "./data_structures/Graph.h"
#include "data_structures/UFDS.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Location{
  string name;
  int id;
  string code;
  bool parking;

  bool operator==(const Location &other) const {
    return id == other.id;
  }
};

Graph<Location>* map = new Graph<Location>();

void read_locations(const string& filename) {
  ifstream infile(filename);
  string line;

  if (!infile.is_open()) {
    cerr << "Could not open file " << filename << std::endl;
    exit(1);
  }

  getline(infile, line);

  while (getline(infile, line)) {
    stringstream ss(line);
    Location loc;
    string parkingStr;

    getline(ss, loc.name, ',');
    ss >> loc.id;
    ss.ignore(); // Ignore comma
    getline(ss, loc.code, ',');
    getline(ss, parkingStr, ',');

    loc.parking = (parkingStr == "1");

    map->addVertex(loc);
  }


  infile.close();

}

int main(){
  read_locations("./For Students/Locations.csv");

  if (!map->getVertexSet().empty()) {
    for (Vertex<Location>* v : map->getVertexSet()) {
      cout << "Location: " << v->getInfo().name << ", ID: " << v->getInfo().id
           << ", Code: " << v->getInfo().code << ", Parking: "
           << (v->getInfo().parking ? "Yes" : "No") << endl;
    }
  } else {
    cerr << "No locations were loaded." << endl;
  }

  delete map;
  return 0;
}