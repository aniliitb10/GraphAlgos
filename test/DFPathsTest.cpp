#include "../include/Paths.h"
#include "../include/DFPaths.h"
#include "../include/Graph.h"
#include "../include/Exception.h"
#include "../include/Util.h"
#include "PathsTest.h"

#include <gtest/gtest.h>
#include <fstream>

struct DFPathsTest : public PathsTest, ::testing::Test
{
};

TEST_F(DFPathsTest, ConnectivityTest)
{
  std::ifstream file{"/home/anil/CLionProjects/GraphAlgos/test/tinyG.txt"};
  DFPaths dfPaths{Graph{file}, 3};

  hasPathsTo(dfPaths, Paths::Vertices{0,1,2,3,4,5,6});
  hasNoPathsTo(dfPaths, Paths::Vertices{7,8,9,10,11,12});
  pathTestWithInvalidVertices(dfPaths, Paths::Vertices{13,14,15,100'000'000});
}

TEST_F(DFPathsTest, PathTest)
{
  std::ifstream file{"/home/anil/CLionProjects/GraphAlgos/test/tinyG.txt"};
  Graph g(file);
  DFPaths dfPaths{g, 3};

  for (size_t index = 0; index <= 6; ++index)
  {
    validatePath(dfPaths, index);
  }

  for (size_t index = 7; index < dfPaths.getGraph().vertices(); ++index)
  {
    validatePath(dfPaths, index, false);
  }

  EXPECT_THROW(dfPaths.pathTo(dfPaths.getGraph().vertices() + 1), InvalidInputException);
  EXPECT_THROW(dfPaths.pathTo(10'000'00), InvalidInputException);
  EXPECT_THROW(dfPaths.pathTo(-1), InvalidInputException);
}

TEST_F(DFPathsTest, ImplemntationTest)
{
  std::istringstream is{"3 4 0 1 0 2 1 2 2 1", std::ios_base::in};
  DFPaths dfPaths{Graph{is}, 0};
  EXPECT_EQ(dfPaths.pathTo(0).size(), 1);
  EXPECT_NE(dfPaths.pathTo(2).size(), dfPaths.pathTo(1).size());
  const auto path2size = dfPaths.pathTo(2).size();
  const auto path1size = dfPaths.pathTo(1).size();

  if (path1size > path2size)
  {
    EXPECT_EQ(path1size - path2size, 1);
  }
  else
  {
    EXPECT_EQ(path2size - path1size, 1);
  }
}