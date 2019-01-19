#include <gtest/gtest.h>

#include "../include/Tree.h"

#include <map>
#include <random>

struct TreeTest : public ::testing::Test
{
  TreeTest()
  {
    _nums.resize(_elemCount);
    std::iota(std::begin(_nums), std::end(_nums), 0);
    std::shuffle(std::begin(_nums), std::end(_nums), std::mt19937{std::random_device{}()});
  }

  constexpr static size_t _elemCount{1000};
  std::vector<size_t> _nums;
};

TEST_F(TreeTest, StdTreeInsertTest)
{
  std::map<size_t, size_t > tree;

  for (size_t index = 0; index < _nums.size(); ++index)
  {
    EXPECT_TRUE(tree.emplace(_nums.at(index), _nums.at(index)).second);
    EXPECT_EQ(index+1, tree.size());
  }

  EXPECT_EQ(_elemCount, tree.size());

  // Re-inserting same element would result into failure
  for (size_t index = 0; index < _elemCount; ++index)
  {
    EXPECT_FALSE(tree.emplace(_nums.at(index), _nums.at(index)).second);
    EXPECT_EQ(_elemCount, tree.size());
  }
}

TEST_F(TreeTest, TreeInsertTest)
{
  Tree<size_t, size_t > tree;

  for (size_t index = 0; index < _nums.size(); ++index)
  {
    EXPECT_TRUE(tree.insert(_nums.at(index), _nums.at(index)).second);
    EXPECT_EQ(index+1, tree.size());
  }

  EXPECT_EQ(_elemCount, tree.size());

  // Re-inserting same element would result into failure
  for (size_t index = 0; index < _elemCount; ++index)
  {
    EXPECT_FALSE(tree.insert(_nums.at(index), _nums.at(index)).second);
    EXPECT_EQ(_elemCount, tree.size());
  }
}