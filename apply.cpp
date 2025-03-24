#include "algorithms.cpp"
#include "data_structures/Graph.h"

void apply_func(Graph<Location>* g, const InputData & inputData, OutputData & output){
  //Since Graph is Graph<Location>
  Location source;
  Location dest;
  source.id = inputData.source;
  dest.id = inputData.destination;
  if(inputData.mode == "driving"){

      if (inputData.includeNode == -1 && inputData.avoidNodes.empty() && inputData.avoidSegments.empty()) {
         dijkstra(g,source);
          auto [path, weight] = getShortestPath(g, dest);
          for (auto v : path) {
              output.BestDrivingRoute.push_back(v->getInfo().id);
          }
          output.best_time = weight;
          //dijkstra already done so we set the distance of the nodes we just used to infinity and then perform dijsktra again
          auto[alt_path, alt_weight] = getAlternativeRoute(g, source, dest,path);

          for (auto v : alt_path) {
              output.AlternativeDrivingRoute.push_back(v->getInfo().id);
          }
          output.time_alternative = alt_weight;

      }
      else {
          for (int node : inputData.avoidNodes) {
              Location temp;
              temp.id = node;

              g -> removeVertex(temp);
          }

        for (auto [first, second] : inputData.avoidSegments) {
              Location temp1;
              Location temp2;
              temp1.id = first;
              temp2.id = second;
              g -> removeEdge(temp1, temp2);
              g -> removeEdge(temp2, temp1);
        }

          dijkstra(g,source);
          auto [path,weight] = getShortestPath(g, dest);

          if (inputData.includeNode != -1) {
              Location includeNode;
              includeNode.id = inputData.includeNode;

              Location sourceLoc;
              sourceLoc.id = inputData.source;

              Location destLoc;
              destLoc.id = inputData.destination;

              dijkstra(g, sourceLoc);
              auto [path1, weight1] = getShortestPath(g, includeNode);

              dijkstra(g, includeNode);
              auto [path2, weight2] = getShortestPath(g, destLoc);

              if (!path1.empty() && !path2.empty() && path1.back() == path2.front()) {
                  path2.erase(path2.begin());  // Remove o includeNode duplicado
              }

              path1.insert(path1.end(), path2.begin(), path2.end());
              path = path1;
              weight = weight1 + weight2;
          }






          for (auto v : path) {
              output.RestrictedDrivingRoute.push_back(v->getInfo().id);
          }

          output.time_restricted = weight;
      }
  }
}
