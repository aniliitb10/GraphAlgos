#include <gtest/gtest.h>
#include <fstream>

#include "../include/DiGraph.h"
#include "../include/Util.h"

struct DiGraphTest : public ::testing::Test
{
  void testAdjacents(const DiGraph& diGraph_, size_t vertex_, const Graph::Adjacents& expectedAdjacents_, bool expectTrue_ = true) const
  {
    const auto& actualAdjacents = diGraph_.getAdjacents(vertex_);
    EXPECT_EQ(Util::compareContent(expectedAdjacents_, actualAdjacents), expectTrue_);
  }
};

TEST_F(DiGraphTest, ConstructionTest)
{
  std::ifstream file{"/home/anil/CLionProjects/GraphAlgos/test/tinyDG.txt"};
  ASSERT_FALSE(file.fail());
  DiGraph dg(file);

  EXPECT_EQ(dg.vertices(), 13);
  EXPECT_EQ(dg.edges(), 22);
}

TEST_F(DiGraphTest, AdjacentVerticesTest)
{
  std::ifstream file{"/home/anil/CLionProjects/GraphAlgos/test/tinyDG.txt"};
  ASSERT_FALSE(file.fail());
  DiGraph dg(file);

  testAdjacents(dg, 0, {5, 1});
  testAdjacents(dg, 0, {6, 2, 1, 5, 4}, false);

  testAdjacents(dg, 1, {});
  testAdjacents(dg, 1, {0, 1}, false);
  testAdjacents(dg, 1, {0, 1, 2}, false);

  testAdjacents(dg, 2, {0, 3});
  testAdjacents(dg, 2, {0, 100'000'000}, false);

  testAdjacents(dg, 3, {5, 2});
  testAdjacents(dg, 4, {3, 2});
  testAdjacents(dg, 5, {4});
  testAdjacents(dg, 6, {9, 4, 8, 0});
  testAdjacents(dg, 7, {6, 9});
  testAdjacents(dg, 8, {6});
  testAdjacents(dg, 9, {11, 10});
  testAdjacents(dg, 10, {12});
  testAdjacents(dg, 11, {4, 12});
  testAdjacents(dg, 12, {9});

  EXPECT_THROW(dg.getAdjacents(-1), InvalidInputException);
  EXPECT_THROW(dg.getAdjacents(dg.vertices()), InvalidInputException);
  EXPECT_THROW(dg.getAdjacents(dg.vertices() + 1), InvalidInputException);
  EXPECT_THROW(dg.getAdjacents(100'000'000), InvalidInputException);
}

TEST_F(DiGraphTest, AddEdgeTest)
{
  std::ifstream file{"/home/anil/CLionProjects/GraphAlgos/test/tinyDG.txt"};
  ASSERT_FALSE(file.fail());
  DiGraph dg(file);

  // If an edge is added, it is added for both vertices
  // and it doesn't impact other vertices. e.g. if an edge from vertex 7 to 2 is added, it doesn't impact vertex 9
  // And edge is added from 7 to 2 only, and not from 2 to 7
  testAdjacents(dg, 7, {6, 9});
  testAdjacents(dg, 2, {0, 3});
  testAdjacents(dg, 9, {11, 10});
  EXPECT_NO_THROW(dg.addEdge(7, 2));

  testAdjacents(dg, 7, {6, 9, 2});
  testAdjacents(dg, 2, {0, 3});
  testAdjacents(dg, 2, {0, 3, 7}, false);
  testAdjacents(dg, 9, {11, 10});

  // By design, it doesn't stop you from adding same edge again
  for (size_t index = 0; index < 100; ++index)
  {
    EXPECT_NO_THROW(dg.addEdge(0,1));
  }

  // But it does throw for invalid vertices
  EXPECT_THROW(dg.addEdge(-1, 0), InvalidInputException);
  EXPECT_THROW(dg.addEdge(dg.vertices(), 0), InvalidInputException);
  EXPECT_THROW(dg.addEdge(dg.vertices(), dg.vertices()), InvalidInputException);
}