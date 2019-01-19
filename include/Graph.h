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
  using Vertex = size_t;
  using Vertices = std::vector<Vertex>;

  using Adjacents = std::vector<Vertex>;
  using AdjacentsList = std::vector<Adjacents>;

  virtual ~Graph() = default;
  Graph(Graph&&) = default;
  Graph(const Graph&) = default;
  /* Expects number of Vertices, number of Edges and then
   * list of pair of vertices making Edges, like:
   * 13
   * 13
   * 0 2
   * 2 5
   * ... so on
   *
   * initAdjList_ is to support DiGraph as we can't call (overloaded) DiGraph's addEdge from constructor of Graph
   * */

  explicit Graph(std::istream& iStream_, bool initAdjList_ = true);
  virtual void addEdge(Vertex from_, Vertex to_);

  Vertex edges() const;
  Vertex vertices() const;
  void print(std::ostream& oStream_) const;
  const Adjacents& getAdjacents(Vertex vertex_) const;

  // Searches linearly in its Adjacents.
  bool hasEdge(Vertex from_, Vertex to_) const;

protected:
  // throws exception if any one of the vertices >= _vertices;
  void validateVertices(const Vertices& vertices_) const;

  AdjacentsList _adjList;
  size_t _edges = 0;
  size_t _vertices = 0;
};