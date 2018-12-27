#pragma once

#include "Exception.h"
#include <istream>
#include <iostream>
#include <set>
#include <functional>

struct Util
{
  static constexpr char NL = '\n';
  static constexpr char WS = ' ';

  template <typename Type>
  static auto readNum(std::istream& ios_, bool keepLooping_)
  {
    Type readValue;
    ios_ >> readValue;

    while (ios_.fail() && keepLooping_)
    {
      ios_.clear();
      ios_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Failed to read integer/number, please try again: ";
      ios_ >> readValue;
    }

    if (ios_.fail()) // is it in failed state
    {
      throw InvalidInputException("Failed to read an integer");
    }
    return readValue;
  }

  static size_t readUInt(std::istream& iStream_, bool keepLooking_ = true)
  {
    return readNum<size_t>(iStream_, keepLooking_);
  }

  static int readInt(std::istream& iStream_, bool keepLooking_ = true)
  {
    return readNum<int>(iStream_, keepLooking_);
  }

  /* To test if the content of two containers are same, irrespective of the order of their content
     e.g. for v1 = {1,2,3} and v2 = {1,3,2}, this function should return true!
     It should be noted that this function, internally, uses a std::multiset
     to store sorted values, so compare for value_type of Iterators must be defined

     There is an optional equalToComp parameter which is called to compare the equality of each pair of values
   */

  template <typename LeftItrType, typename RightItrType, typename EqualToComp = std::equal_to<>>
  static bool compareContent(LeftItrType leftBegin_, LeftItrType leftEnd_, RightItrType rightBegin_,
                             RightItrType rightEnd_,
                             EqualToComp equalToComp = EqualToComp())
  {
    // when Iterators are random access iterators, std::distance returns in constant time!
    if (std::distance(leftBegin_, leftEnd_) != std::distance(rightBegin_, rightEnd_))
    {
      return false;
    }

    // Can't use std::set, because then, {1,2,2,3} and {1,2,3,3} would look same!
    std::multiset<typename std::iterator_traits<LeftItrType>::value_type> leftSet{leftBegin_, leftEnd_};
    std::multiset<typename std::iterator_traits<RightItrType>::value_type> rightSet{rightBegin_, rightEnd_};

    auto leftSetItr = std::begin(leftSet);
    auto rightSetItr = std::begin(rightSet);

    for (; (leftSetItr != std::end(leftSet)) && (rightSetItr != std::end(rightSet)); leftSetItr++, rightSetItr++)
    {
      if (!equalToComp(*leftSetItr, *rightSetItr))
      {
        return false;
      }
    }

    return true;
  }
};