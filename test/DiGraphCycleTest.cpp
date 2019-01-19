#include <gtest/gtest.h>
#include <fstream>

#include "../include/DiGraphCycle.h"
#include "../include/Util.h"

struct DiGraphCycleTest : public ::testing::Test
{
  void cyclePathVerification(const DiGraph& diGraph_, Paths::Vertices expectedPath_)
  {
    auto source = expectedPath_.front();
    EXPECT_EQ(expectedPath_.front(), expectedPath_.back());

    for (size_t index = 1; index < expectedPath_.size(); ++index)
    {
      EXPECT_TRUE(diGraph_.hasEdge(expectedPath_.at(index-1), expectedPath_.at(index)));
    }
  }
};

TEST_F(DiGraphCycleTest, hasCycleTest)
{
  std::ifstream file{"/home/anil/CLionProjects/GraphAlgos/test/tinyDG.txt"};
  ASSERT_FALSE(file.fail());
  DiGraph dg(file);

  DiGraphCycle dgCycle{dg};
  EXPECT_TRUE(dgCycle.hasCycle());
  Paths::Vertices path, expectedPath{5,4,2,3,5};
  dgCycle.cyclePath(std::back_inserter(path));
  EXPECT_TRUE(Util::compareContent(path, expectedPath));
  cyclePathVerification(dg, expectedPath);
}

TEST_F(DiGraphCycleTest, NoCycleTest)
{
std::ifstream file{"/home/anil/CLionProjects/GraphAlgos/test/tinyDAG.txt"};
ASSERT_FALSE(file.fail());
DiGraph dg(file);

DiGraphCycle dgCycle{dg};
EXPECT_FALSE(dgCycle.hasCycle());
}