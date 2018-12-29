#pragma once

#include "Graph.h"

#include <string>
#include <vector>

/*
 * This is base class for both DFS and BFS
 * */

class Search
{
public:
  using BoolList = std::basic_string<bool>;
  using UnIntList = std::vector<size_t>;
  using Vertices = UnIntList;

  Search(Graph graph_, size_t source_);
  bool hasPathTo(size_t target_) const;
  const Graph& getGraph() const;
  size_t getSource() const;
  virtual Vertices pathTo(size_t target_) const;
  void print(std::ostream& os_) const;

protected:
  virtual void search(const Graph& graph_, size_t target_) = 0;

  Graph     _graph;
  size_t    _source; // Source for the search algorithm
  BoolList  _visited; // Has this vertex been visited?
  UnIntList _edgeTo; // Reached to index for first time from value

private:
  // throws exception if any one of the vertices >= _graph.vertices();
  void validateVertices(const std::initializer_list<Vertices::value_type>& vertices_) const;
};