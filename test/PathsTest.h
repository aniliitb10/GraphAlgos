#include <gtest/gtest.h>

#include "../include/Paths.h"
#include "../include/Exception.h"
#include "../include/DFPaths.h"

#include <fstream>

struct PathsTest
{
  virtual void hasPathsTo(const Paths& paths_, Paths::Vertices vertices_);
  virtual void hasNoPathsTo(const Paths& paths_, const Paths::Vertices& vertices_);
  virtual void pathTestWithInvalidVertices(const Paths& paths_, const Paths::Vertices& vertices_);
  void validatePath(const Paths& paths_, size_t target_, bool pathExpected_ = true);
};

inline void PathsTest::hasPathsTo(const Paths& paths_, Paths::Vertices vertices_)
{
  for (const auto& vertex : vertices_)
  {
    EXPECT_TRUE(paths_.hasPathTo(vertex));
  }
}

inline void PathsTest::hasNoPathsTo(const Paths& paths_, const Paths::Vertices& vertices_)
{
  for (const auto& vertex : vertices_)
  {
    EXPECT_FALSE(paths_.hasPathTo(vertex));
  }
}

inline void PathsTest::pathTestWithInvalidVertices(const Paths& paths_, const Paths::Vertices& vertices_)
{
  for (const auto& vertex : vertices_)
  {
    EXPECT_THROW(paths_.hasPathTo(vertex), InvalidInputException);
  }
}

inline void PathsTest::validatePath(const Paths& paths_, Paths::Vertex target_, bool pathExpected_)
{
  const auto& path = paths_.pathTo(target_);
  EXPECT_NE(pathExpected_, path.empty());

  if (path.empty())
  {
    return;
  }

  const auto from = paths_.getSource();
  EXPECT_EQ(from, path.front());
  EXPECT_EQ(target_, path.back());
  const auto& graph = paths_.getGraph();

  if (path.size() == 1)
  {
    EXPECT_EQ(target_, paths_.getSource());
  }

  for (auto itr = std::begin(path); itr < std::prev(std::end(path)); ++itr)
  {
    EXPECT_TRUE(graph.hasEdge(*itr, *(std::next(itr)))) << "No edge between "  << *itr << " and " << *(std::next(itr));
  }
}