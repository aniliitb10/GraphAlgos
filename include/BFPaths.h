#pragma once

#include "../include/Paths.h"
#include "../include/Graph.h"

class BFPaths : public Paths
{
public:
  explicit BFPaths(Graph graph_, Paths::Vertex source_);

protected:
  void search(const Graph &graph_, Vertex target_) override;
};