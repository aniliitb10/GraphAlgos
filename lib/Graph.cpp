#include "../include/Graph.h"
#include "../include/Util.h"
#include "../include/Exception.h"

#include <sstream>

Graph::Graph(std::istream &iStream_, bool initAdjList_)
{
  _vertices = Util::readUInt(iStream_);
  _adjList.resize(_vertices);

  if (initAdjList_)
  {
    auto edges = Util::readUInt(iStream_);
    for (size_t index = 0; index < edges; ++index)
    {
      auto from = Util::readUInt(iStream_);
      auto to = Util::readUInt(iStream_);

      addEdge(from, to);
    }
  }
}

void Graph::addEdge(Vertex from_, Vertex to_)
{
  validateVertices({from_, to_});
  _adjList.at(from_).push_back(to_);
  _adjList.at(to_).push_back(from_);
  _edges++;
}

size_t Graph::edges() const
{
  return _edges;
}

size_t Graph::vertices() const
{
  return _vertices;
}

const Graph::Adjacents &Graph::getAdjacents(Vertex vertex_) const
{
  validateVertices({vertex_});
  return _adjList.at(vertex_);
}

bool Graph::hasEdge(Vertex from_, Vertex to_) const
{
  validateVertices({from_, to_});
  const auto& adjacents = _adjList.at(from_);
  return std::find(std::begin(adjacents), std::end(adjacents), to_) != std::end(adjacents);
}

void Graph::validateVertices(const Vertices& vertices_) const
{
  for (auto vertex : vertices_)
  {
    if (vertex >= _vertices)
    {
      std::ostringstream os;
      os << "Invalid vertex: " << vertex << ", it must be less than " << _vertices;
      throw InvalidInputException(os.str());
    }
  }
}

void Graph::print(std::ostream &oStream_) const
{
  oStream_ << "Vertices: " << _vertices << Util::NL;
  oStream_ << "Edges:    " << _edges    << Util::NL;

  for (size_t index = 0; index < _adjList.size(); ++index)
  {
    oStream_ << index << " -> [ ";

    const auto& adjacents = _adjList.at(index);
    for (const auto& adjacent : adjacents)
    {
      oStream_ << adjacent << Util::WS;
    }
    oStream_ << "]" << Util::NL;
  }
}