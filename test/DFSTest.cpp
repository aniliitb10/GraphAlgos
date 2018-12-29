#include "../include/DFS.h"
#include "../include/Graph.h"
#include "../include/Exception.h"
#include "../include/Util.h"

#include <gtest/gtest.h>
#include <fstream>

struct DFSTest : public ::testing::Test
{
  void validatePath(const DFS& dfs_, size_t target_, bool pathExpected_ = true)
  {
    const auto& path = dfs_.pathTo(target_);
    EXPECT_NE(pathExpected_, path.empty());

    if (path.empty())
    {
      return;
    }

    const auto from = dfs_.getSource();
    EXPECT_EQ(from, path.front());
    EXPECT_EQ(target_, path.back());
    const auto& graph = dfs_.getGraph();

    if (path.size() == 1)
    {
      EXPECT_EQ(target_, dfs_.getSource());
    }

    for (auto itr = std::begin(path); itr < std::prev(std::end(path)); ++itr)
    {
      EXPECT_TRUE(graph.hasEdge(*itr, *(std::next(itr)))) << "No edge between "  << *itr << " and " << *(std::next(itr));
    }
  }
};

TEST_F(DFSTest, ConnectivityTest)
{
  std::ifstream file{"/home/anil/CLionProjects/GraphAlgos/test/tinyG.txt"};
  Graph g(file);

  DFS dfs{g, 3};
  EXPECT_TRUE(dfs.hasPathTo(0));
  EXPECT_TRUE(dfs.hasPathTo(1));
  EXPECT_TRUE(dfs.hasPathTo(2));
  EXPECT_TRUE(dfs.hasPathTo(3));
  EXPECT_TRUE(dfs.hasPathTo(4));
  EXPECT_TRUE(dfs.hasPathTo(5));
  EXPECT_TRUE(dfs.hasPathTo(6));

  EXPECT_FALSE(dfs.hasPathTo(7));
  EXPECT_FALSE(dfs.hasPathTo(8));
  EXPECT_FALSE(dfs.hasPathTo(9));
  EXPECT_FALSE(dfs.hasPathTo(10));
  EXPECT_FALSE(dfs.hasPathTo(11));
  EXPECT_FALSE(dfs.hasPathTo(12));

  EXPECT_THROW(dfs.hasPathTo(13), InvalidInputException);
  EXPECT_THROW(dfs.hasPathTo(14), InvalidInputException);
  EXPECT_THROW(dfs.hasPathTo(15), InvalidInputException);
  EXPECT_THROW(dfs.hasPathTo(100'000'000), InvalidInputException);
}

TEST_F(DFSTest, PathTest)
{
  std::ifstream file{"/home/anil/CLionProjects/GraphAlgos/test/tinyG.txt"};
  Graph g(file);
  DFS dfs{g, 3};

  for (size_t index = 0; index <= 6; ++index)
  {
    validatePath(dfs, index);
  }

  for (size_t index = 7; index < dfs.getGraph().vertices(); ++index)
  {
    validatePath(dfs, index, false);
  }

  EXPECT_THROW(dfs.pathTo(dfs.getGraph().vertices() + 1), InvalidInputException);
  EXPECT_THROW(dfs.pathTo(10'000'00), InvalidInputException);
  EXPECT_THROW(dfs.pathTo(-1), InvalidInputException);
}