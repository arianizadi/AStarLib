#include "AStarLib/IDAStar.h"
#include "MyGraph.h"

#include <iostream>
#include <vector>

void printGrid(MyGraph& graph,
               const std::vector< std::pair< int, int > >& path) {
  int width = graph.getWidth();
  int height = graph.getHeight();

  for(int y = 0; y < height; ++y) {
    for(int x = 0; x < width; ++x) {
      if(graph.isObstacle(x, y)) {
        std::cout << "# ";
      } else if(std::find(path.begin(), path.end(), std::make_pair(x, y))
                != path.end()) {
        std::cout << "* ";
      } else {
        std::cout << ". ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

auto main() -> int {
  const int width = 50;
  const int height = 50;

  MyGraph graph(width, height);
  graph.setObstacle(3, 2);
  graph.setObstacle(3, 3);
  graph.setObstacle(3, 4);
  graph.setObstacle(3, 5);

  AStarLib::IDAStar< std::pair< int, int >, double > idastar;

  // Start at the bottom-left corner
  std::pair< int, int > start = {0, 0};
  std::pair< int, int > goal
      = {width - 1, 0}; // Go to the bottom-right corner initially

  std::vector< std::pair< int, int > > idapath;

  // Attempt area coverage from left to right
  while(start.second < height) {
    idapath = idastar.findPath(graph, start, goal);

    // Print grid with current path
    std::cout << "IDA* Path:" << std::endl;
    printGrid(graph, idapath);

    // Move start to the next row
    start.second++;

    // Update goal to the new position in the same row
    goal = {width - 1, start.second};
  }

  return 0;
}
