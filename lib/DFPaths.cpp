#include "../include/DFPaths.h"

#include <stack>

DFPaths::DFPaths(Graph graph_, Paths::Vertex source_):
Paths(std::move(graph_), source_)
{
  search(_graph, _source);
}

void DFPaths::search(const Graph &graph_, Paths::Vertex target_)
{
  // if we put this line inside for loop, then source would never be marked visited
  _visited.at(target_) = true;

  for (const auto& adjacent : graph_.getAdjacents(target_))
  {
    if (!_visited.at(adjacent))
    {
      _edgeTo.at(adjacent) = target_;
      _colors.at(adjacent) = !_colors.at(target_);
      // _visited.at(target_) = true; commented out as it has been kept at the top of this function
      search(graph_, adjacent);
    }
    else
    {
      if (_colors.at(adjacent) == _colors.at(target_))
      {
        _isBipartite = false;
      }
    }
  }
}

/*
void DFPaths::search(const Graph &graph_, Paths::Vertex target_)
{
  std::stack<Paths::Vertex> verticesToVisit;
  verticesToVisit.push(target_);
  _edgeTo.at(target_) = target_;
  _colors.at(target_) = false;

  while (!verticesToVisit.empty())
  {
    auto vertex = verticesToVisit.top(); // It would be buggy to capture vertex by reference
    verticesToVisit.pop();

    if (!_visited.at(vertex))
    {
      _visited.at(vertex) = true;
      for (const auto& adjacent : graph_.getAdjacents(vertex))
      {
        if (!_visited.at(adjacent))
        {
          verticesToVisit.push(adjacent);
          _edgeTo.at(adjacent) = vertex;
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
}*/
