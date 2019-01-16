#pragma once

#include "Graph.h"
#include "Paths.h"

#include <vector>

/* CC is short for Connected Components*/

class CC
{
public:
  explicit CC(Graph graph_);
  bool connected(Paths::Vertex from_, Paths::Vertex to_) const;
  size_t count() const;
  size_t id(Paths::Vertex vertex_) const;

private:
  void validateVertices(const Paths::Vertices& vertices_) const;
  void dfs(const Graph& graph_, Paths::Vertex vertex_);

  Graph _graph;
  std::vector <size_t> _ids;
  Paths::BoolList _visited;
  size_t _idCount = 0;
};