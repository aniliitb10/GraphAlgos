#include "../include/DiGraph.h"
#include "../include/Util.h"

DiGraph::DiGraph(std::istream &iStream_) : Graph(iStream_, false)
{
  auto edges = Util::readUInt(iStream_);

  for (auto edge = 0; edge < edges; ++edge)
  {
    auto from = Util::readUInt(iStream_);
    auto to = Util::readUInt(iStream_);
    addEdge(from, to);
  }
}

void DiGraph::addEdge(Vertex from_, Vertex to_)
{
  validateVertices({from_, to_});
  _adjList.at(from_).push_back(to_);
  _edges++;
}