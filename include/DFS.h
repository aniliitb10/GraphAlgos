#pragma once

#include "Search.h"

class DFS : public Search
{
public:
  using Path = Graph::Adjacents;

  DFS(Graph graph_, size_t source_);

private:
  void search(const Graph &graph_, size_t target_) override;
};