#include <gtest/gtest.h>

#include "../include/Util.h"

#include <string>

struct SplitTest : public ::testing::Test
{
};

TEST_F(SplitTest, StringSplitTest)
{
  using StrList = Util::StrList;

  const std::string source{"let's test it"};
  Util::StrList splits;
  Util::split(source, Util::WS, std::back_inserter(splits));
  EXPECT_EQ(splits.size(), 3);

  Util::StrList expectedSplits = {"let's", "test", "it"};
  EXPECT_EQ(expectedSplits, splits);

  splits.clear();
  Util::split("let's test                       it", Util::WS, std::back_inserter(splits));
  EXPECT_EQ(expectedSplits, splits);

  splits.clear();
  Util::split("test", Util::WS, std::back_inserter(splits));
  EXPECT_EQ(StrList{"test"}, splits);

  splits.clear();
  Util::split("test ", Util::WS, std::back_inserter(splits));
  EXPECT_EQ(StrList{"test"}, splits);

  splits.clear();
  Util::split(" test", Util::WS, std::back_inserter(splits));
  EXPECT_EQ(StrList{"test"}, splits);

  splits.clear();
  Util::split(" test ", Util::WS, std::back_inserter(splits));
  EXPECT_EQ(StrList{"test"}, splits);
}

TEST_F(SplitTest, StringSplitTestStrSep)
{
  using StrList = Util::StrList;

  const std::string source {"mangoes, bananas, apples"};
  const StrList expectedSplits = {"mangoes", "bananas", "apples"};

  StrList splits;
  Util::split(source, ", ", std::back_inserter(splits));
  EXPECT_EQ(expectedSplits, splits);

  splits.clear();
  Util::split(source, "bananas", std::back_inserter(splits));
  EXPECT_NE(expectedSplits, splits);

  const StrList expectedSplits2 = {"mangoes, ", ", apples"};
  splits.clear();
  Util::split(source, "bananas", std::back_inserter(splits));
  EXPECT_EQ(expectedSplits2, splits);
}

TEST_F(SplitTest, charCountTest)
{
  EXPECT_EQ(1, std::size(""));

  EXPECT_EQ(0, Util::char_count(""));
  EXPECT_EQ(1, Util::char_count('a'));
  EXPECT_EQ(5, Util::char_count("chars"));
  EXPECT_EQ(5, Util::char_count(std::string{"chars"}));
}

TEST_F(SplitTest, FirstNotOfTest)
{
  EXPECT_EQ(2, Util::find_first_not_of("  first name", Util::WS, 0));
  EXPECT_EQ(2, Util::find_first_not_of("  first name", " ", 0));

  EXPECT_EQ(2, Util::find_first_not_of("__first_name", '_', 0));
  EXPECT_EQ(2, Util::find_first_not_of("__first_name", "_", 0));

  EXPECT_EQ(2, Util::find_first_not_of("  first name", Util::WS, 2));
  EXPECT_EQ(2, Util::find_first_not_of("  first name", " ", 2));

  EXPECT_EQ(10, Util::find_first_not_of("  first   name", Util::WS, 7));
  EXPECT_EQ(10, Util::find_first_not_of("  first   name", " ", 7));

  EXPECT_EQ(0, Util::find_first_not_of("  first name", "Unknown"));

  EXPECT_EQ(4, Util::find_first_not_of("name name", "name"));

  EXPECT_EQ(4, Util::find_first_not_of("name name", "name", 0));
  EXPECT_EQ(1, Util::find_first_not_of("name name", "name", 1));
  EXPECT_EQ(2, Util::find_first_not_of("name name", "name", 2));
  EXPECT_EQ(3, Util::find_first_not_of("name name", "name", 3));
  EXPECT_EQ(4, Util::find_first_not_of("name name", "name", 4));

  EXPECT_EQ(std::string::npos, Util::find_first_not_of("name name", "name", 5));

  EXPECT_EQ(6, Util::find_first_not_of("name name", "name", 6));
  EXPECT_EQ(7, Util::find_first_not_of("name name", "name", 7));
  EXPECT_EQ(8, Util::find_first_not_of("name name", "name", 8));
  EXPECT_EQ(std::string::npos, Util::find_first_not_of("name name", "name", 9));
}

TEST_F(SplitTest, DecayEqTest)
{
  static_assert(Util::decay_eq_v<int, int>);
  static_assert(Util::decay_eq_v<int&, int>);
  static_assert(Util::decay_eq_v<const int&, int>);

  static_assert(Util::decay_eq_v<char*, char*>);
  static_assert(Util::decay_eq_v<char[], char*>);

  auto chars = "testing chars";
  static_assert(Util::decay_eq_v<decltype(chars), const char*>);

  constexpr auto explicitConstChars = "testing chars";
  static_assert(Util::decay_eq_v<decltype(explicitConstChars), const char*>);
}