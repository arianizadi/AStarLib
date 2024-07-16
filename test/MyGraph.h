#ifndef ASTARLIB_MYGRAPH_H
#define ASTARLIB_MYGRAPH_H

#include "AStarLib/Graph.h"

#include <cmath> // For abs()
#include <vector>

class MyGraph : public AStarLib::Graph< std::pair< int, int >, double > {
public:
  MyGraph(int width, int height) :
      width_(width), height_(height),
      grid_(width, std::vector< bool >(height, false)) {
  }

  auto getNeighbors(const std::pair< int, int >& node) const
      -> std::vector< std::pair< int, int > > override {
    std::vector< std::pair< int, int > > neighbors;
    // Define possible movements (8 directions: N, NE, E, SE, S, SW, W,
    // NW)
    static const std::vector< std::pair< int, int > > directions
        = {{1, 0},
           {-1, 0},
           {0, 1},
           {0, -1},
           {1, 1},
           {1, -1},
           {-1, 1},
           {-1, -1}};

    for(const auto& dir : directions) {
      int neighbor_x = node.first + dir.first;
      int neighbor_y = node.second + dir.second;

      if(isValidLocation(neighbor_x, neighbor_y)
         && !isObstacle(neighbor_x, neighbor_y)) {
        neighbors.emplace_back(neighbor_x, neighbor_y);
      }
    }

    return neighbors;
  }

  auto getCost(const std::pair< int, int >& from,
               const std::pair< int, int >& to) const -> double override {
    // Euclidean distance as the cost metric
    return std::sqrt(std::pow(to.first - from.first, 2)
                     + std::pow(to.second - from.second, 2));
  }

  auto getHeuristic(const std::pair< int, int >& node,
                    const std::pair< int, int >& goal) const
      -> double override {
    // Euclidean distance heuristic
    return std::sqrt(std::pow(goal.first - node.first, 2)
                     + std::pow(goal.second - node.second, 2));
  }

  void setObstacle(int x, int y) {
    if(isValidLocation(x, y)) {
      grid_[x][y] = true;
    }
  }

  void clearObstacle(int x, int y) {
    if(isValidLocation(x, y)) {
      grid_[x][y] = false;
    }
  }

  auto getWidth() -> int {
    return width_;
  }

  auto getHeight() -> int {
    return height_;
  }

  auto isValidLocation(int x, int y) const -> bool {
    return x >= 0 && x < width_ && y >= 0 && y < height_;
  }

  auto isObstacle(int x, int y) const -> bool {
    return grid_[x][y];
  }

private:
  int width_;
  int height_;
  std::vector< std::vector< bool > >
      grid_; // True for obstacles, False for clear
};

#endif // ASTARLIB_MYGRAPH_H
