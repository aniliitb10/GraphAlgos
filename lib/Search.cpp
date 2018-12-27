#include "../include/Exception.h"

#include "../include/Search.h"
#include <limits>
#include <stack>

Search::Search(Graph graph_, size_t source_):
_graph(std::move(graph_)),
_source(source_)
{
  _marked.resize(_graph.vertices(), false);
  _edgeTo.resize(_graph.vertices(), std::numeric_limits<size_t>::max());
}

bool Search::hasPathTo(size_t target_) const
{
  if (target_ >= _graph.vertices())
  {
    throw InvalidInputException("Vertex number can't be greater than the number of vertices(" + std::to_string(_graph.vertices()) + ")");
  }

  return _marked.at(target_);
}

Search::Vertices Search::pathTo(size_t target_) const
{
  if (!hasPathTo(target_))
  {
    return Graph::Adjacents{};
  }

  auto vertex = target_;
  std::stack<size_t> targetToSourcePath;

  while(_edgeTo.at(vertex) != vertex)
  {
    targetToSourcePath.push(_edgeTo.at(vertex));
    vertex = _edgeTo.at(vertex);
  }
  targetToSourcePath.push(vertex);

  Vertices sourceToTargetPath;
  while(!targetToSourcePath.empty())
  {
    sourceToTargetPath.push_back(targetToSourcePath.top());
    targetToSourcePath.pop();
  }

  return sourceToTargetPath;
}
