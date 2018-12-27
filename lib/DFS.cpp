#include "../include/DFS.h"

#include <stack>

DFS::DFS(Graph graph_, size_t source_):
Search(std::move(graph_), source_)
{
  search(_graph, _source);
}

void DFS::search(const Graph &graph_, size_t target_)
{
  std::stack<size_t> vertices;
  vertices.push(target_);
  _edgeTo.at(target_) = target_;

  while (!vertices.empty())
  {
    const auto& vertex = vertices.top();
    vertices.pop();

    if (!_marked.at(vertex))
    {
      _marked.at(vertex) = true;
      for (const auto& adjacent : graph_.getAdjacents(vertex))
      {
        vertices.push(adjacent);
        _edgeTo.at(adjacent) = vertex;
      }
    }
  }
}