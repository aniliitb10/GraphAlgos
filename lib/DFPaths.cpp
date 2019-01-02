#include "../include/DFPaths.h"

#include <stack>

DFPaths::DFPaths(Graph graph_, Paths::Vertex source_):
Paths(std::move(graph_), source_)
{
  search(_graph, _source);
}

void DFPaths::search(const Graph &graph_, Paths::Vertex target_)
{
  std::stack<Paths::Vertex> verticesToVisit;
  verticesToVisit.push(target_);
  _edgeTo.at(target_) = target_;
  _visited.at(target_) = true;

  while (!verticesToVisit.empty())
  {
    auto vertex = verticesToVisit.top(); // It would be buggy to capture vertex by reference
    verticesToVisit.pop();

    for (const auto& adjacent : graph_.getAdjacents(vertex))
    {
      if (!_visited.at(adjacent))
      {
        _edgeTo.at(adjacent) = vertex;
        _visited.at(adjacent) = true;
        verticesToVisit.push(adjacent);
      }
    }
  }
}