#include "algorithms.cpp"
#include "data_structures/Graph.h"

void apply_func(Graph<Location>* g, const InputData & inputData, OutputData & output){
  //Since Graph is Graph<Location>
  Location temp1;
  Location temp2;
  temp1.id = inputData.source;
  temp2.id = inputData.destination;
  if(inputData.mode == "driving"){
      if (inputData.avoidNodes.empty() && inputData.avoidSegments.empty() && inputData.includeNode == 0) {
         dijkstra(g,temp1);
          auto [path, weight] = getShortestPath(g, temp2);
          for (auto v : path) {
              output.BestDrivingRoute.push_back(v->getInfo().id);
          }
          output.best_time = weight;


      }
  }
}
