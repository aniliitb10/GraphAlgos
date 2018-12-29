#include "../include/DFS.h"

#include <stack>

DFS::DFS(Graph graph_, size_t source_):
Search(std::move(graph_), source_)
{
  search(_graph, _source);
}

void DFS::search(const Graph &graph_, size_t target_)
{
  std::stack<size_t> verticesToVisit;
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