#include <gtest/gtest.h>

#include "../include/Tree.h"

#include <map>
#include <random>

struct TreeTest : public ::testing::Test
{
  constexpr static size_t ElemCount{1000'000};
};

TEST_F(TreeTest, StdTreeInsertTest)
{
  std::map<size_t, size_t > tree;
  std::vector<size_t> nums(ElemCount);
  std::iota(std::begin(nums), std::end(nums), 0);
  std::shuffle(std::begin(nums), std::end(nums), std::mt19937{std::random_device{}()});

  for (size_t index = 0; index < nums.size(); ++index)
  {
    EXPECT_TRUE(tree.emplace(nums.at(index), nums.at(index)).second);
    EXPECT_EQ(index+1, tree.size());
  }

  EXPECT_EQ(ElemCount, tree.size());

  // Re-inserting same element would result into failure
  for (size_t index = 0; index < ElemCount; ++index)
  {
    EXPECT_FALSE(tree.emplace(nums.at(index), nums.at(index)).second);
    EXPECT_EQ(ElemCount, tree.size());
  }
}

TEST_F(TreeTest, TreeInsertTest)
{
  Tree<size_t, size_t > tree;
  std::vector<size_t> nums(ElemCount);
  std::iota(std::begin(nums), std::end(nums), 0);
  std::shuffle(std::begin(nums), std::end(nums), std::mt19937{std::random_device{}()});

  for (size_t index = 0; index < nums.size(); ++index)
  {
    EXPECT_TRUE(tree.insert(nums.at(index), nums.at(index)).second);
    EXPECT_EQ(index+1, tree.size());
  }

  EXPECT_EQ(ElemCount, tree.size());

  // Re-inserting same element would result into failure
  for (size_t index = 0; index < ElemCount; ++index)
  {
    EXPECT_FALSE(tree.insert(nums.at(index), nums.at(index)).second);
    EXPECT_EQ(ElemCount, tree.size());
  }
}