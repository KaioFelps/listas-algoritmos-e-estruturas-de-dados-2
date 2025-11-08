#pragma once

#include "sort_algorithms/utils.hpp"
#include <span>

namespace core::sort_algorithms
{

template <typename T> size_t ___find_biggest_el_pos(const std::span<T> vector)
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

template <typename T> void selection_sort(std::span<T> vector)
{
  using internal::___swap;
  if (vector.size() <= 1) return;

  for (size_t i = vector.size() - 1; i > 0; i--)
  {
    auto biggest_el_from_subspan_pos =
        ___find_biggest_el_pos(vector.subspan(0, i + 1));
    if (biggest_el_from_subspan_pos == i) continue;
    swap(vector, biggest_el_from_subspan_pos, i);
  }
}

} // namespace core::sort_algorithms
