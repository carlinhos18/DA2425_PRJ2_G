//
// Created by ceraizi on 26-03-2025.
//

#ifndef MODE_H
#define MODE_H

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

string getMode();
unordered_set<int> getAvoidNodes();
vector<pair<int, int>> getAvoidSegments();
int getIncludeNode();
int getMaxWalk();
int getValidInteger(const string &prompt);
InputData HandleUserInput();

#endif //MODE_H
