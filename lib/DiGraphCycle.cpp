#include "../include/DiGraphCycle.h"
#include <limits>

DiGraphCycle::DiGraphCycle(const DiGraph& diGraph_)
{
  _visited.resize(diGraph_.vertices(), false);
  _onStack.resize(diGraph_.vertices(), false);
  _edgeTo.resize(diGraph_.vertices(), std::numeric_limits<Paths::Vertex>::max());

  for (size_t vertex = 0; vertex < diGraph_.vertices(); ++vertex)
  {
    if (!_visited.at(vertex))
    {
      dfs(diGraph_, vertex);
    }
  }
}

bool DiGraphCycle::hasCycle() const
{
  return !_cyclePath.empty();
}

void DiGraphCycle::dfs(const DiGraph &diGraph_, Paths::Vertex vertex_)
{
  _visited.at(vertex_) = true;
  _onStack.at(vertex_) = true;

  for (const auto& adjacent : diGraph_.getAdjacents(vertex_))
  {
    if (_cyclePath.empty() && _onStack.at(adjacent))
    {
      extractCyclePath(diGraph_, adjacent, vertex_);
    }

    if (!_visited.at(adjacent))
    {
      _edgeTo.at(adjacent) = vertex_;
      dfs(diGraph_, adjacent);
    }
  }
  _onStack.at(vertex_) = false;
}

void DiGraphCycle::extractCyclePath(const DiGraph& diGraph_, Paths::Vertex onStack_, Paths::Vertex lastVertex_)
{
  // check for self cycle:
  if (onStack_ == lastVertex_) return;

  // check for mutual connection (2 -> 3 and 3 -> 2)
  if (diGraph_.hasEdge(onStack_, lastVertex_)) return;

  _cyclePath.push_back(onStack_);
  _cyclePath.push_back(lastVertex_);

  auto edgeTo = _edgeTo.at(lastVertex_);
  while (edgeTo != onStack_)
  {
    _cyclePath.push_back(edgeTo);
    edgeTo = _edgeTo.at(edgeTo);
  }
  _cyclePath.push_back(onStack_);
}