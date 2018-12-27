#include "../include/DFS.h"
#include "../include/Graph.h"
#include "../include/Exception.h"

#include <gtest/gtest.h>
#include <fstream>

struct DFSTest : public ::testing::Test
{

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