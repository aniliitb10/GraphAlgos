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
  virtual Vertices pathTo(size_t target_) const;

protected:
  virtual void search(const Graph& graph_, size_t target_) = 0;

  Graph     _graph;
  size_t    _source; // Source for the search algorithm
  BoolList  _marked; // Has this vertex been visited?
  UnIntList _edgeTo; // Reached to index for first time from value
};