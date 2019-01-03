#pragma once

#include "Paths.h"

class DFPaths : public Paths
{
public:
  using Path = Graph::Adjacents;

  DFPaths(Graph graph_, Paths::Vertex source_);

private:

  /* There is a difference between non-recursive implementation of DFS and BFS
   * (and I am NOT talking about just stack vs queue, of course)
   * - Check the way _visited.at(vertex), for a vertex, is being set in DFS
   * - For edges: 0-1, 0-2, 1-2, and 2-1 with vertex 0 as the source, following is what
   *   we get (Let's call the implementation in which we simply replace queue of BFS
   *   with stack as Non-Recursive-Stack-Queue-Replacement):
   * ------------------------------------------------------------------------
   * Recursive        Non-Recursive   Non-Recursive-Stack-Queue-Replacement |
   * ------------------------------------------------------------------------
   * _edgeTo[0] = 0   _edgeTo[0] = 0  _edgeTo[0] = 0
   * _edgeTo[1] = 0   _edgeTo[1] = 2  _edgeTo[1] = 0
   * _edgeTo[2] = 1   _edgeTo[2] = 0  _edgeTo[2] = 0
   *
   * As you can see, Non-Recursive-Stack-Queue-Replacement is much like BFS where
   * both vertices 1 and 2 were reached from vertex 0
   * */
  void search(const Graph &graph_, Paths::Vertex target_) override;
};