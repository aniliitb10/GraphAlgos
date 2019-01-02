#include <gtest/gtest.h>
#include <fstream>

#include "../include/Graph.h"
#include "../include/BFPaths.h"
#include "PathsTest.h"

struct BFSPathTest : PathsTest, public ::testing::Test
{
};

TEST_F(BFSPathTest, ConnectivityTest)
{
  std::ifstream file{"/home/anil/CLionProjects/GraphAlgos/test/tinyG.txt"};
  Graph g(file);

  BFPaths bfPaths{g, 3};
  hasPathsTo(bfPaths, Paths::Vertices{0,1,2,3,4,5,6});
  hasNoPathsTo(bfPaths, Paths::Vertices{7,8,9,10,11,12});
  pathTestWithInvalidVertices(bfPaths, Paths::Vertices{13,14,15,100'000'000});
}

TEST_F(BFSPathTest, PathsTests)
{
  std::ifstream file{"/home/anil/CLionProjects/GraphAlgos/test/tinyG.txt"};
  BFPaths bfPaths{Graph{file}, 3};

  for (size_t index = 0; index <= 6; ++index)
  {
    validatePath(bfPaths, index);
  }

  for (size_t index = 7; index < bfPaths.getGraph().vertices(); ++index)
  {
    validatePath(bfPaths, index, false);
  }

  EXPECT_THROW(bfPaths.pathTo(bfPaths.getGraph().vertices() + 1), InvalidInputException);
  EXPECT_THROW(bfPaths.pathTo(10'000'00), InvalidInputException);
  EXPECT_THROW(bfPaths.pathTo(-1), InvalidInputException);
}

TEST_F(BFSPathTest, ShortestPathTest)
{
  std::ifstream file{"/home/anil/CLionProjects/GraphAlgos/test/tinyG.txt"};
  BFPaths bfPaths{Graph{file}, 3};

  EXPECT_EQ(bfPaths.pathTo(0).size(), 3);
  EXPECT_EQ(bfPaths.pathTo(1).size(), 4);
  EXPECT_EQ(bfPaths.pathTo(2).size(), 4);
  EXPECT_EQ(bfPaths.pathTo(3).size(), 1); // self
  EXPECT_EQ(bfPaths.pathTo(4).size(), 2);
  EXPECT_EQ(bfPaths.pathTo(5).size(), 2);
  EXPECT_EQ(bfPaths.pathTo(6).size(), 3);

  // There is no path from source to target
  EXPECT_EQ(bfPaths.pathTo(7).size(), 0);
  EXPECT_EQ(bfPaths.pathTo(8).size(), 0);
  EXPECT_EQ(bfPaths.pathTo(9).size(), 0);
  EXPECT_EQ(bfPaths.pathTo(10).size(), 0);
  EXPECT_EQ(bfPaths.pathTo(11).size(), 0);
  EXPECT_EQ(bfPaths.pathTo(12).size(), 0);
}