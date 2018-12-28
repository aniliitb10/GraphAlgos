#include "../include/Graph.h"
#include "../include/Util.h"

#include <gtest/gtest.h>
#include <set>
#include <fstream>

struct GraphTest : public ::testing::Test
{
  /* This will be helpful in testing when a vertex has multiple adjacent vertices
   * Couldn't use templated variadic args because:
   *  - 1) If we call like: testAdjacents(g,0,6,2,1,5), it failed to compile as there was narrowing conversion (int to size_t)
   *  - 2) The type of all parameters was fixed (size_t), so type pack looked over-kill*/
  bool testAdjacents(const Graph& graph_, size_t vertex_, std::initializer_list<size_t> vertices_, bool expectTrue_ = true) const
  {
    const auto& actualAdjacents = graph_.getAdjacents(vertex_);
    const Graph::Adjacents expectedAdjacents = vertices_;
    EXPECT_EQ(Util::compareContent(actualAdjacents, expectedAdjacents), expectTrue_);
  }
};

TEST_F(GraphTest, ConstructionTest)
{
  std::ifstream file{"/home/anil/CLionProjects/GraphAlgos/test/tinyG.txt"};
  Graph g(file);

  EXPECT_EQ(g.vertices(), 13);
  EXPECT_EQ(g.edges(), 13);
}

TEST_F(GraphTest, AdjacentVerticesTest)
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

TEST_F(GraphTest, AddEdgeTest)
{
  std::ifstream file{"/home/anil/CLionProjects/GraphAlgos/test/tinyG.txt"};
  Graph g(file);

  // If an edge is added, it is added for both vertices
  // and it doesn't impact other vertices. e.g. if an edge from vertex 2 to 7 is added, it doesn't impact vertex 8
  testAdjacents(g, 7, {8});
  testAdjacents(g, 2, {0});
  testAdjacents(g, 8, {7});
  EXPECT_NO_THROW(g.addEdge(7, 2));

  testAdjacents(g, 7, {8, 2});
  testAdjacents(g, 2, {0, 7});
  testAdjacents(g, 8, {7});

  // By design, it doesn't stop you from adding same edge again
  for (size_t index = 0; index < 100; ++index)
  {
    EXPECT_NO_THROW(g.addEdge(0,1));
  }

  // But it does throw for invalid vertices
  EXPECT_THROW(g.addEdge(-1, 0), InvalidInputException);
  EXPECT_THROW(g.addEdge(g.vertices(), 0), InvalidInputException);
  EXPECT_THROW(g.addEdge(g.vertices(), g.vertices()), InvalidInputException);
}
