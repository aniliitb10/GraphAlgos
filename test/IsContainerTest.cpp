#include "../include/Util.h"

#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <set>
#include <stack>
#include <queue>
#include <map>
#include <array>
#include <string>

struct IsContainerTest : ::testing::Test
{
  template <typename T>
  void testWithFundamentalTypes()
  {
    static_assert(std::is_fundamental_v<T>); // first verify that it is indeed fundamental
    EXPECT_FALSE(Util::is_container_v<T>);
  }
};

TEST_F(IsContainerTest, STLContainerTest)
{
  EXPECT_TRUE(Util::is_container_v<std::vector<int>>);
  EXPECT_TRUE(Util::is_container_v<std::list<int>>);
  EXPECT_TRUE(Util::is_container_v<std::set<int>>);
  EXPECT_TRUE(Util::is_container_v<std::string>);
  EXPECT_TRUE(Util::is_container_v<std::basic_string<bool>>);

  // As function-like macros will not compile with multiple template types
  static_assert(Util::is_container_v<std::array<int, 10>>);
  static_assert(Util::is_container_v<std::map<int, int>>);
  static_assert(Util::is_container_v<std::unordered_map<int, int>>);

  EXPECT_FALSE(Util::is_container_v<std::stack<int>>);
  EXPECT_FALSE(Util::is_container_v<std::queue<int>>);
}

TEST_F(IsContainerTest, CustomContainerTest)
{
  // As Util::is_container_v only checks for begin() and end()
  // it is easy to cheat :P
  struct BadContainerWithoutEnd
  {
    nullptr_t begin() { return nullptr; };
  };

  struct BadContainerWithoutBegin
  {
    nullptr_t end() { return nullptr; };
  };

  //TODO:: Figure out why this is not good enough to cheat std::begin(std::declval<T>())
  struct GoodContainer
  {
    int begin() { return 0;}
    int end() { return 0;}
  };

  EXPECT_TRUE(Util::is_container_v<GoodContainer>);
  EXPECT_FALSE(Util::is_container_v<BadContainerWithoutBegin>);
  EXPECT_FALSE(Util::is_container_v<BadContainerWithoutEnd>);
}

TEST_F(IsContainerTest, FundamentalTypes)
{
  testWithFundamentalTypes<bool>();
  testWithFundamentalTypes<char>();
  testWithFundamentalTypes<u_char >();
  testWithFundamentalTypes<short>();
  testWithFundamentalTypes<u_short>();
  testWithFundamentalTypes<int>();
  testWithFundamentalTypes<unsigned int>();

  testWithFundamentalTypes<long>();
  testWithFundamentalTypes<unsigned long>();
  testWithFundamentalTypes<long long>();
  testWithFundamentalTypes<unsigned long long>();

  testWithFundamentalTypes<float>();
  testWithFundamentalTypes<double>();
  testWithFundamentalTypes<void>();

  testWithFundamentalTypes<nullptr_t>();
}