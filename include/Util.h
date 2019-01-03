#pragma once

#include "Exception.h"
#include <istream>
#include <iostream>
#include <set>
#include <functional>
#include <type_traits>

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
  static bool compareContent(LeftItrType leftBegin_, LeftItrType leftEnd_, RightItrType rightBegin_, RightItrType rightEnd_,
                             EqualToComp equalToComp_ = EqualToComp())
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
      if (!equalToComp_(*leftSetItr, *rightSetItr))
      {
        return false;
      }
    }

    return true;
  }

  /* A way to determine if a class is a container (precisely, an iterable) or not
   * It checks if the class has begin() const and end() const declared
   * (thanks to std::declval for testing the declaration of these functions without instantiating the class). */

  template <typename, typename = std::void_t <>>
  struct is_container : std::false_type{};

  template <typename T>
  struct is_container <T, std::void_t<decltype(std::begin(std::declval<T>())),
                                      decltype(std::end(std::declval<T>()))
                                     >
                      > : std::true_type {};

  template <typename T>
  constexpr static bool is_container_v = is_container<T>::value;

  /* Now using is_container_v to call compareContent with Containers
   * Notice the use of std::enable_if_t: this function is enabled only when Container1 and Container2
   * are containers (according to is_container_v)*/
  template <class Container1, class Container2, class EqualToComp = std::equal_to<>>
  static auto compareContent(const Container1& left_, const Container2& right_, EqualToComp equalToComp_ = EqualToComp())
       -> std::enable_if_t <is_container_v<Container1> && is_container_v<Container2>, bool>
  {
    return compareContent(std::begin(left_), std::end(left_), std::begin(right_), std::end(right_), equalToComp_);
  }
};