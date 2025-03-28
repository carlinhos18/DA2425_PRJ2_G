#include "apply_utils.cpp"


void apply_func(Graph<Location>* g, const InputData & inputData, OutputData & output){
  //Since Graph is Graph<Location>
  Location source;
  Location dest;
  source.id = inputData.source;
  dest.id = inputData.destination;
  if(inputData.mode == "driving"){
        //* NO RESTRICTIONS DRIVING *//
      if (!HasDriveRestriction(inputData)){
         dijkstra(g,source, false);

          auto [path, weight] = getShortestPath(g, dest);
          SetBestDriveRoute(output, path, weight);

          //dijkstra already done so we set the distance of the nodes we just used to infinity and then perform dijsktra again
          auto[alt_path, alt_weight] = getAlternativeRoute(g, source, dest,path);

          SetAlternativeDriveRoute(output, alt_path, alt_weight);

      }
      else {
          RemoveNodes(g, inputData); // we dont need to check if it has avoid Nodes

          RemoveEdges(g, inputData); // same thing

          dijkstra(g,source, false);
          auto [path,weight] = getShortestPath(g, dest);

          if (HasIncludeNode(inputData)) {
              Location includeNode;
              includeNode.id = inputData.includeNode;

              Location sourceLoc;
              sourceLoc.id = inputData.source;

              Location destLoc;
              destLoc.id = inputData.destination;

              dijkstra(g, sourceLoc, false);
              auto [path1, weight1] = getShortestPath(g, includeNode);

              dijkstra(g, includeNode, false);
              auto [path2, weight2] = getShortestPath(g, destLoc);

              if (!path1.empty() && !path2.empty() && path1.back() == path2.front()) {
                  path2.erase(path2.begin());  // Remove o includeNode duplicado
              }

              path1.insert(path1.end(), path2.begin(), path2.end());
              path = path1;
              weight = weight1 + weight2;
          }

          SetRestrictedDriveRoute(output,path,weight);
      }
  }
    if (inputData.mode == "driving-walking") {
        RemoveNodes(g, inputData);

        RemoveEdges(g, inputData);

        source.parking = GetParking(g, source);
        dest.parking = GetParking(g, dest);

        auto[BestDriveRoute, time_d, parkingNode,
        BestWalkRoute, time_w,
        total_time] = eco_friendly_route(g, source, dest,inputData.MaxWalkTime);

        if (BestDriveRoute.empty() || BestWalkRoute.empty()) {
            output.message = "No possible route with max. walking time of " + to_string(inputData.MaxWalkTime) + " minutes.";

            // Fazer aqui as rotas alternativas



        } else {
            SetDriveWalkRoute(output, BestDriveRoute, time_d, parkingNode, BestWalkRoute, time_w, total_time);
        }
    }

}
