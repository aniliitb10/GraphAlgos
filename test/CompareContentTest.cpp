
#include "../include/Util.h"
#include <gtest/gtest.h>

#include <vector>
#include <list>
#include <set>
#include <unordered_set>

struct CompareContentTest : public ::testing::Test
{
};

TEST_F(CompareContentTest, simpleTest)
{
  std::vector<int> intVec{10,2,3,4,4};
  std::multiset<int>intSet{2,3,4,10,4};
  std::list<int>intList{3,4,2,10,4};
  std::unordered_multiset<int>intUnSet{10,2,4,3,4};

  EXPECT_TRUE(Util::compareContent(std::begin(intVec), std::end(intVec), std::begin(intSet), std::end(intSet)));
  EXPECT_TRUE(Util::compareContent(std::begin(intVec), std::end(intVec), std::begin(intUnSet), std::end(intUnSet)));
  EXPECT_TRUE(Util::compareContent(std::begin(intVec), std::end(intVec), std::begin(intList), std::end(intList)));

  EXPECT_TRUE(Util::compareContent(std::begin(intSet), std::end(intSet), std::begin(intList), std::end(intList)));
  EXPECT_TRUE(Util::compareContent(std::begin(intSet), std::end(intSet), std::begin(intUnSet), std::end(intUnSet)));

  EXPECT_TRUE(Util::compareContent(std::begin(intList), std::end(intList), std::begin(intUnSet), std::end(intUnSet)));
}

TEST_F(CompareContentTest, EqualityOperatorTest)
{
  class Person;

  class Person
  {
  public:
    Person(std::string name_, size_t age_):
      _name(std::move(name_)),
      _age(age_){}

    size_t getAge() const { return _age; }

    bool operator<(const Person& person_) const
    {
      return this->_age < person_._age;
    }

  private:
    std::string _name;
    size_t      _age;
  };

  std::vector<Person> persons {Person{"kumar1", 26}, Person{"kumar2", 27}};
  std::list<size_t> ages{26, 27};
  std::list<size_t> wrongAges{27, 28};

  auto equalityComparator = [](const Person& person_, size_t age_) { return person_.getAge() == age_; };

  EXPECT_TRUE(Util::compareContent(std::begin(persons), std::end(persons), std::begin(ages), std::end(ages), equalityComparator));
  EXPECT_FALSE(Util::compareContent(std::begin(persons), std::end(persons), std::begin(wrongAges), std::end(wrongAges),equalityComparator));
}