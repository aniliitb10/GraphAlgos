#include "../include/BFPaths.h"
#include <queue>

BFPaths::BFPaths(Graph graph_, Paths::Vertex source_) : Paths(std::move(graph_), source_)
{
  search(_graph, _source);
}

void BFPaths::search(const Graph &graph_, Paths::Vertex target_)
{
  std::queue<Paths::Vertex> verticesToVisit;
  verticesToVisit.push(target_);
  _visited.at(target_) = true;

  while (!verticesToVisit.empty())
  {
    Paths::Vertex vertex = verticesToVisit.front();
    verticesToVisit.pop();

    for (const auto& adjacent : graph_.getAdjacents(vertex))
    {
      if (!_visited.at(adjacent))
      {
        verticesToVisit.push(adjacent);
        _visited.at(adjacent) = true;
        _edgeTo.at(adjacent) = vertex; // this isn't required at the top as source shouldn't be reached from another vertex
        _colors.at(adjacent) = !_colors.at(vertex);
      }
      else
      {
        // here _colors.at(adjacent) doesn't give the default value as it has been assigned once
        if (_colors.at(adjacent) == _colors.at(vertex))
        {
          _isBipartite = false;
        }
      }
    }
  }
}