// include/AStarLib/IDAStar.h
#ifndef ASTARLIB_IDASTAR_H
#define ASTARLIB_IDASTAR_H

#include "Graph.h"

#include <algorithm>
#include <limits>
#include <vector>

namespace AStarLib {

  template < typename Node, typename Cost >
  class IDAStar {
  public:
    IDAStar() = default;

    auto findPath(const Graph< Node, Cost >& graph,
                  const Node& start,
                  const Node& goal) -> std::vector< Node > {
      Cost threshold = graph.getHeuristic(start, goal);
      std::vector< Node > path;
      path.push_back(start);

      while(true) {
        Cost temp = search(graph, path, 0, threshold, goal);
        if(temp == std::numeric_limits< Cost >::max()) {
          return std::vector< Node >(); // No path found
        } else if(temp == 0) {
          return path; // Path found
        }
        threshold = temp;
      }
    }

  private:
    auto search(const Graph< Node, Cost >& graph,
                std::vector< Node >& path,
                Cost g,
                Cost threshold,
                const Node& goal) -> Cost {
      Node current = path.back();
      Cost f = g + graph.getHeuristic(current, goal);
      if(f > threshold) {
        return f;
      }
      if(current == goal) {
        return 0;
      }

      Cost min = std::numeric_limits< Cost >::max();
      for(const Node& neighbor : graph.getNeighbors(current)) {
        if(std::find(path.begin(), path.end(), neighbor) == path.end()) {
          path.push_back(neighbor);
          Cost temp = search(graph,
                             path,
                             g + graph.getCost(current, neighbor),
                             threshold,
                             goal);
          if(temp == 0) {
            return 0;
          }
          if(temp < min) {
            min = temp;
          }
          path.pop_back();
        }
      }
      return min;
    }
  };

} // namespace AStarLib

#endif // ASTARLIB_IDASTAR_H
