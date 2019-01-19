#pragma once

#include "Graph.h"

#include <sstream>

class DiGraph : public Graph
{
public:
  explicit DiGraph(std::istream& iStream_);
  ~DiGraph() override = default;

  void addEdge(Vertex from_, Vertex to_) override;
};