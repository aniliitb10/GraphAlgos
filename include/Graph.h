#pragma once

#include <istream>
#include <vector>

/*
 * I have been following algorithms-2 from coursera.org and
 * this class is just an implementation of of ideas presented in that course.
 * This graph uses adjacency list
 * */

class Graph
{
public:
  using Adjacents = std::vector<size_t>;
  using AdjacentsList = std::vector<Adjacents>;

  /* Expects number of Vertices, number of Edges and then
   * list of pair of vertices making Edges, like:
   * 13
   * 13
   * 0 2
   * 2 5
   * ... so on
   * */
  explicit Graph(std::istream& iStream_);
  void addEdge(size_t from_, size_t to_);

  size_t edges() const;
  size_t vertices() const;
  void print(std::ostream& oStream_) const;
  const Adjacents& getAdjacents(size_t vertex_) const;

private:
  AdjacentsList _adjList;
  size_t _edges;
  size_t _vertices;
};