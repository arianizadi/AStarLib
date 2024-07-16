#include "AStarLib/IDAStar.h"
#include "MyGraph.h"

#include <iostream>
#include <random>
#include <thread>
#include <vector>

void addRandomObstacles(MyGraph& graph, int numObstacles) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution< int > dis(1, graph.getWidth() - 1);

  for(int i = 0; i < numObstacles; ++i) {
    int x = dis(gen);
    int y = dis(gen);
    graph.setObstacle(x, y);
  }
}

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
  const int width = 10;
  const int height = 10;

  MyGraph graph(width, height);

  addRandomObstacles(graph, 25);

  AStarLib::IDAStar< std::pair< int, int >, double > idastar;

  // Start at the bottom-left corner
  std::pair< int, int > start = {0, 0};
  std::pair< int, int > goal
      = {width - 1, 0}; // Go to the bottom-right corner initially

  std::vector< std::pair< int, int > > idapath;

  std::vector< std::chrono::milliseconds > durations;

  // Attempt area coverage from left to right
  while(start.second < height) {
    if(graph.isObstacle(start.first, start.second)) {
      start.first++;
      continue;
    }

    if(graph.isObstacle(goal.first, goal.second)) {
      goal.first--;
      continue;
    }

    auto startTime = std::chrono::high_resolution_clock::now();

    idapath = idastar.findPath(graph, start, goal);

    // Print grid with current path
    std::cout << "IDA* Path:" << std::endl;
    printGrid(graph, idapath);

    // Move start to the next row
    start.second++;

    // Update goal to the new position in the same row
    goal = {width - 1, start.second};

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration
        = std::chrono::duration_cast< std::chrono::milliseconds >(
            endTime - startTime);

    std::cout << "Time taken: " << duration.count() << " milliseconds"
              << std::endl;

    durations.push_back(duration);

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  for(auto i : durations) {
    std::cout << "Row: " << static_cast< int >(i.count())
              << " milliseconds" << std::endl;
  }

  return 0;
}
