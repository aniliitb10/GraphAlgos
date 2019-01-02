#pragma once

#include "Graph.h"

#include <string>
#include <vector>

/*
 * This is base class for both DFPaths and BFSPaths
 * */

class Paths
{
public:
  using BoolList = std::basic_string<bool>;
  using Vertex = size_t;
  using Vertices = std::vector<Vertex>;

  Paths(Graph graph_, Vertex source_);
  bool hasPathTo(Vertex target_) const;
  const Graph& getGraph() const;
  Vertex getSource() const;
  virtual Vertices pathTo(Vertex target_) const;

  // Only for debugging
  void print(std::ostream& os_) const;

protected:
  virtual void search(const Graph& graph_, Vertex target_) = 0;

  Graph     _graph;
  size_t    _source; // Source for the search algorithm
  BoolList  _visited; // Has this vertex been visited?
  Vertices  _edgeTo; // Reached to index for first time from value

private:
  // throws exception if any one of the vertices >= _graph.vertices();
  void validateVertices(const std::initializer_list<Vertices::value_type>& vertices_) const;
};