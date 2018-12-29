#include "../include/Exception.h"

#include "../include/Search.h"
#include "../include/Util.h"
#include <limits>
#include <stack>
#include <sstream>

Search::Search(Graph graph_, size_t source_):
_graph(std::move(graph_)),
_source(source_)
{
  _visited.resize(_graph.vertices(), false);
  _edgeTo.resize(_graph.vertices(), std::numeric_limits<size_t>::max());
}

bool Search::hasPathTo(size_t target_) const
{
  validateVertices({target_});
  return _visited.at(target_);
}

Search::Vertices Search::pathTo(size_t target_) const
{
  validateVertices({target_});
  if (!hasPathTo(target_))
  {
    return Graph::Adjacents{};
  }

  auto vertex = target_;
  std::stack<size_t> targetToSourcePath;

  targetToSourcePath.push(target_);
  while(_edgeTo.at(vertex) != vertex)
  {
    targetToSourcePath.push(_edgeTo.at(vertex));
    vertex = _edgeTo.at(vertex);
  }

  Vertices sourceToTargetPath;
  while(!targetToSourcePath.empty())
  {
    sourceToTargetPath.push_back(targetToSourcePath.top());
    targetToSourcePath.pop();
  }

  return sourceToTargetPath;
}

void Search::print(std::ostream &os_) const
{
  os_ << "Source: " << _source << Util::NL
      << "Are vertices marked:" << Util::NL << std::boolalpha;

  for (size_t index = 0; index < _visited.size(); ++index)
  {
    os_ << index << Util::WS <<  _visited.at(index) << Util::NL;
  }

  os_ << "EdgeTo details: " << Util::NL;
  for (size_t index = 0; index < _edgeTo.size(); ++index)
  {
    if (_visited.at(index))
    {
      os_ << index << Util::WS <<  _edgeTo.at(index) << Util::NL;
    }

  }

  os_ << "Graph details:" << Util::NL;
  _graph.print(os_);
}

size_t Search::getSource() const
{
  return _source;
}

const Graph &Search::getGraph() const
{
  return _graph;
}

void Search::validateVertices(const std::initializer_list<Vertices::value_type> &vertices_) const
{
  for (auto vertex : vertices_)
  {
    if (vertex >= _graph.vertices())
    {
      std::ostringstream os;
      os << "Invalid vertex: " << vertex << ", it must be less than " << _graph.vertices();
      throw InvalidInputException(os.str());
    }
  }
}
