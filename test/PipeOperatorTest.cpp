#include "../include/PipeOperator.h"

#include <gtest/gtest.h>
#include <vector>
#include <set>

struct PipeOperatorTest : public ::testing::Test
{};

TEST_F(PipeOperatorTest, PushBackTest)
{
  using IntVec = std::vector<int>;

  IntVec nums{1,2,3,4,5,8,8,90};
  auto evenNums = nums | filter([](auto num_) { return (num_ % 2) == 0;});
  IntVec expectedFiltered{2,4,8,8,90};
  EXPECT_EQ(expectedFiltered, evenNums);
  EXPECT_NE(nums, evenNums);
}

TEST_F(PipeOperatorTest, InsertTest)
{
  using IntSet = std::set<int>;

  IntSet nums{2,3,4,5,8,42,91};
  auto evenNums = nums | filter([](auto num_) { return (num_ % 2) == 0;});
  IntSet expectedFilteredNums {2,4,8,42};
  EXPECT_EQ(expectedFilteredNums, evenNums);
  EXPECT_NE(nums, evenNums);
}