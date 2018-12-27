#include "../include/Graph.h"
#include "../include/Util.h"

#include <gtest/gtest.h>
#include <set>
#include <fstream>

struct GraphTest : public ::testing::Test
{
  bool compareAdjacents(const Graph::Adjacents& actual_, const Graph::Adjacents& expected_) const
  {
    return Util::compareContent(std::begin(actual_), std::end(actual_), std::begin(expected_), std::end(expected_));
  }

  /* This will be helpful in testing when a vertex has multiple adjacent vertices
   * Couldn't use templated variadic args because:
   *  - 1) If we call like: testAdjacents(g,0,6,2,1,5), it failed to compile as there was narrowing conversion (int to size_t)
   *  - 2) The type of all parameters was fixed (size_t), so type pack looked over-kill*/
  bool testAdjacents(const Graph& graph_, size_t vertex_, std::initializer_list<size_t> vertices_, bool expectTrue_ = true) const
  {
    const auto& actualAdjacents = graph_.getAdjacents(vertex_);
    const Graph::Adjacents expectedAdjacents = vertices_;
    if (expectTrue_)
    {
      EXPECT_TRUE(compareAdjacents(actualAdjacents, expectedAdjacents));
    }
    else
    {
      EXPECT_FALSE(compareAdjacents(actualAdjacents, expectedAdjacents));
    }
  }
};

TEST_F(GraphTest, adjacentVerticesTest)
{
  std::ifstream file{"/home/anil/CLionProjects/GraphAlgos/test/tinyG.txt"};
  Graph g(file);

  testAdjacents(g, 0, {6, 2, 1, 5});
  testAdjacents(g, 0, {6, 2, 1, 5, 4}, false);

  testAdjacents(g, 1, {0});
  testAdjacents(g, 1, {0, 1}, false);
  testAdjacents(g, 1, {0, 1, 2}, false);

  testAdjacents(g, 2, {0});
  testAdjacents(g, 2, {0, 100'000'000}, false);

  testAdjacents(g, 3, {4, 5});
  testAdjacents(g, 4, {3, 5, 6});
  testAdjacents(g, 5, {3, 4, 0});
  testAdjacents(g, 6, {0, 4});
  testAdjacents(g, 7, {8});
  testAdjacents(g, 8, {7});
  testAdjacents(g, 9, {10, 11, 12});
  testAdjacents(g, 10, {9});
  testAdjacents(g, 11, {9, 12});
  testAdjacents(g, 12, {9, 11});

  EXPECT_THROW(g.getAdjacents(-1), InvalidInputException);
  EXPECT_THROW(g.getAdjacents(13), InvalidInputException);
  EXPECT_THROW(g.getAdjacents(100'000'000), InvalidInputException);
}

