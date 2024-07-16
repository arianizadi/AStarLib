// include/AStarLib/Graph.h
#ifndef ASTARLIB_GRAPH_H
#define ASTARLIB_GRAPH_H

#include <vector>

namespace AStarLib {

  template < typename Node, typename Cost >
  class Graph {
  public:
    virtual ~Graph() = default;

    // Method to get neighbors of a given node
    virtual auto
    getNeighbors(const Node& node) const -> std::vector< Node > = 0;

    // Method to compute the cost between two nodes
    virtual auto getCost(const Node& from, const Node& to) const -> Cost
                                                                    = 0;

    // Method to compute the heuristic cost from a node to the goal
    virtual auto getHeuristic(const Node& node,
                              const Node& goal) const -> Cost = 0;
  };

} // namespace AStarLib

#endif // ASTARLIB_GRAPH_H
