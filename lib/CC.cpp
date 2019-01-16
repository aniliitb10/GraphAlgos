#include "../include/CC.h"
#include "../include/Exception.h"

#include <limits>
#include <sstream>

CC::CC(Graph graph_):
_graph(std::move(graph_))
{
  _ids.resize(_graph.vertices(), std::numeric_limits<std::size_t>::max());
  _visited.resize(_graph.vertices(), false);

  for (auto vertex = 0; vertex < _graph.vertices(); ++vertex)
  {
    if (!_visited.at(vertex))
    {
      dfs(_graph, vertex);
      _idCount++;
    }
  }
}

bool CC::connected(Paths::Vertex from_, Paths::Vertex to_) const
{
  validateVertices(Paths::Vertices{from_, to_});
  return _ids.at(from_) == _ids.at(to_);
}

size_t CC::id(Paths::Vertex vertex_) const
{
  validateVertices(Paths::Vertices{vertex_});
  return _ids.at(vertex_);
}

void CC::validateVertices(const Paths::Vertices& vertices_) const
{
  for (auto vertex : vertices_)
  {
    if (vertex >= _ids.size())
    {
      std::ostringstream os;
      os << "Invalid vertex: " << vertex << ", should not be greater than total number of vertices: " << _graph.vertices();
      throw Exception(os.str());
    }
  }
}

void CC::dfs(const Graph &graph_, Paths::Vertex vertex_)
{
  _visited.at(vertex_) = true;
  _ids.at(vertex_) = _idCount;

  for (auto vertex  : graph_.getAdjacents(vertex_))
  {
    if (!_visited.at(vertex))
    {
      dfs(graph_, vertex);
    }
  }
}

size_t CC::count() const
{
  return _idCount;
}
