#pragma once

#include "sort_algorithms/utils.hpp"
#include <span>

namespace core::sort_algorithms
{

namespace internal
{

template <typename T> size_t find_biggest_el_pos(const std::span<T> vector)
{
  auto biggest_el_pos = 0;

  for (size_t i = 1; i < vector.size(); i++)
  {
    auto &biggest_el = vector[biggest_el_pos];
    if (vector[i] <= biggest_el) continue;
    biggest_el_pos = i;
  }

  return biggest_el_pos;
}

} // namespace internal

template <typename T> void selection_sort(std::span<T> vector)
{
  using namespace internal;

  if (vector.size() <= 1) return;

  for (size_t i = vector.size() - 1; i > 0; i--)
  {
    const auto subspan = vector.subspan(0, i + 1);
    auto pos_of_biggest_el_from_subspan = find_biggest_el_pos(subspan);
    if (pos_of_biggest_el_from_subspan == i) continue;
    swap(vector, pos_of_biggest_el_from_subspan, i);
  }
}

} // namespace core::sort_algorithms
