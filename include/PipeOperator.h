#pragma once

#include <type_traits>
#include <algorithm>
#include <iterator>

/* To be used as:
 *  auto evenNums = nums | filter([](auto num_){ return num_ % 2 == 0; }); */


/* Some Utils to determine if container has push_back method*/
template <typename Container, typename = void>
struct has_push_back : std::false_type{};

template <typename Container>
struct has_push_back<Container, std::void_t<decltype(std::declval<Container>().push_back(std::declval<typename Container::value_type>()))>> : std::true_type{};

template <typename Container>
constexpr bool has_push_back_v = has_push_back<Container>::value;

/* Some Utils to determine if container has insert method
 * Usage: has_insert_v<Container> should be true for Container having insert method*/
template <typename Container, typename = void>
struct has_insert : std::false_type{};

template <typename Container>
struct has_insert<Container, std::void_t<decltype(std::declval<Container>().insert(std::declval<typename Container::value_type>()))>> : std::true_type{};

template <typename Container>
constexpr bool has_insert_v = has_insert<Container>::value;

/* Now some help to compiler to resolve the Pipe operator*/
template <typename Func>
struct FilterProxy
{
  const Func& _func;
};

template <typename Func>
auto filter(const Func& func_) -> FilterProxy<Func>
{
  return FilterProxy<Func>{func_};
}

template <typename Container, typename Func>
auto operator|(const Container& container_, const FilterProxy<Func>& funcProxy_) -> std::enable_if_t <has_push_back_v<Container>, Container>
{
  Container filtered;
  for (const auto elem : container_)
  {
    if (funcProxy_._func(elem))
    {
      filtered.push_back(elem);
    }
  }

  return filtered;
}

template <typename Container, typename Func>
auto operator|(const Container& container_, const FilterProxy<Func>& funcProxy_) -> std::enable_if_t <has_insert_v<Container>, Container>
{
  Container filtered;
  for (const auto& elem : container_)
  {
    if (funcProxy_._func(elem))
    {
      filtered.insert(elem);
    }
  }
  return filtered;
}
