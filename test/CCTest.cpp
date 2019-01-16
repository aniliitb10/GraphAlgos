#include "../include/CC.h"
#include "../include/Exception.h"

#include <gtest/gtest.h>
#include <fstream>

struct CCTest : public ::testing::Test
{
  void sameIdTest(const CC& cc_, const Paths::Vertices& vertices_)
  {
    const auto id = cc_.id(vertices_.front());
    for (auto vertex : vertices_)
    {
      EXPECT_EQ(cc_.id(vertex), id);
    }
  }
};

TEST_F(CCTest, SimpleTest)
{
  std::ifstream fileHandle("/home/anil/CLionProjects/GraphAlgos/test/tinyG.txt");
  ASSERT_TRUE(fileHandle.good());
  Graph graph{fileHandle};
  CC cc(std::move(graph));

  EXPECT_EQ(cc.count(), 3);
  sameIdTest(cc, Paths::Vertices{0,1,2,3,4,5,6});
  sameIdTest(cc, Paths::Vertices{7,8});
  sameIdTest(cc, Paths::Vertices{9,10,11,12});
}

TEST_F(CCTest, VerticesTest)
{
  std::ifstream fileHandle("/home/anil/CLionProjects/GraphAlgos/test/tinyG.txt");
  ASSERT_TRUE(fileHandle.good());
  Graph graph{fileHandle};
  CC cc(graph);

  EXPECT_THROW(cc.id(std::numeric_limits<std::size_t>::max()), Exception);
  EXPECT_THROW(cc.id(graph.vertices()), Exception);

  EXPECT_THROW(cc.id(cc.connected(std::numeric_limits<std::size_t>::max(), 0)), Exception);
  EXPECT_THROW(cc.id(cc.connected(graph.vertices(), 0)), Exception);
}
