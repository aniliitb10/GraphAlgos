#include "../include/Graph.h"
#include "../include/Util.h"
#include "../include/Exception.h"

#include <sstream>

Graph::Graph(std::istream &iStream_)
{
  _vertices = Util::readUInt(iStream_);
  _edges = Util::readUInt(iStream_);

  _adjList.resize(_vertices);
  
  for (size_t index = 0; index < _edges; ++index)
  {
    addEdge(Util::readUInt(iStream_), Util::readUInt(iStream_));
  }
}

void Graph::addEdge(size_t from_, size_t to_)
{
  if ((from_ >= _vertices) || (to_ >= _vertices))
  {
    std::ostringstream os;
    os << "Vertex number (" << std::to_string(from_) << " and/or " << std::to_string(to_)
       << ") must be less than the number of vertices (" << std::to_string(_vertices);

    throw InvalidInputException(os.str());
  }

  _adjList.at(from_).push_back(to_);
  _adjList.at(to_).push_back(from_);
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
  if (vertex_ >= _vertices)
  {
    throw InvalidInputException("Vertex number must be less than the number of vertices (" + std::to_string(_vertices) + ")");
  }
  return _adjList.at(vertex_);
}