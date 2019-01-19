#pragma once

#include "DiGraph.h"
#include "Paths.h"

class DiGraphCycle
{
public:
  explicit DiGraphCycle(const DiGraph& diGraph_);
  bool hasCycle() const;

  template <typename OutItr>
  void cyclePath(OutItr outItr_);

private:
  void dfs (const DiGraph& diGraph_, Paths::Vertex vertex_);
  void extractCyclePath(const DiGraph& diGraph_, Paths::Vertex onStack_, Paths::Vertex lastVertex_);

  Paths::BoolList _visited;
  Paths::Vertices _edgeTo;
  Paths::Vertices _cyclePath;
  Paths::BoolList _onStack;
};

template<typename OutItr>
void DiGraphCycle::cyclePath(OutItr outItr_)
{
  for (auto revItr = std::rbegin(_cyclePath); revItr != std::rend(_cyclePath); ++revItr)
  {
    outItr_ = *(revItr);
  }
}