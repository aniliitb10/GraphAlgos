#pragma once

#include "Paths.h"

class DFPaths : public Paths
{
public:
  using Path = Graph::Adjacents;

  DFPaths(Graph graph_, Paths::Vertex source_);

private:
  void search(const Graph &graph_, Paths::Vertex target_) override;
};