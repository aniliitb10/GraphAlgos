#include "../include/Graph.h"
#include "../include/Util.h"
#include "../include/Exception.h"

#include <sstream>

Graph::Graph(std::istream &iStream_)
{
  _vertices = Util::readUInt(iStream_);
  _edges = 0;
  auto edges = Util::readUInt(iStream_);

  _adjList.resize(_vertices);
  
  for (size_t index = 0; index < edges; ++index)
  {
    addEdge(Util::readUInt(iStream_), Util::readUInt(iStream_));
  }
}

void Graph::addEdge(size_t from_, size_t to_)
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

const Graph::Adjacents &Graph::getAdjacents(size_t vertex_) const
{
  validateVertices({vertex_});
  return _adjList.at(vertex_);
}

bool Graph::hasEdge(size_t from_, size_t to_) const
{
  validateVertices({from_, to_});
  const auto& adjacents = _adjList.at(from_);
  return std::find(std::begin(adjacents), std::end(adjacents), to_) != std::end(adjacents);
}

void Graph::validateVertices(const std::initializer_list<Adjacents::value_type>& vertices_) const
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
