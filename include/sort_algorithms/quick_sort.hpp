#pragma once

#include "sort_algorithms/utils.hpp"
#include <span>

namespace core::sort_algorithms
{

/**
 * The `___partition` function ensures that every element from `vec`
 * that is smaller than `pivot` is placed on its left and the bigger ones
 * on its right.
 *
 * @param vec The vector to partition.
 * @param pivot_pos The position of the choosen `pivot`.
 * @returns The new `pivot`s position.
 */
template <typename T> size_t ___partition(std::span<T> vec, size_t pivot_pos)
{
  auto pivot = vec[pivot_pos];

  /**
   * The border who separates those elements smaller than the pivot from the
   * bigger ones
   */
  size_t border_cursor = 0;

  const auto vec_size = vec.size();
  for (size_t current_el_cursor = 0; current_el_cursor < vec_size;
       current_el_cursor++)
  {
    auto &element = vec[current_el_cursor];

    if (element > pivot || current_el_cursor == pivot_pos) continue;

    internal::___swap(vec, current_el_cursor, border_cursor);
    border_cursor++;
  }

  internal::___swap(vec, pivot_pos, border_cursor);
  return border_cursor;
}

} // namespace core::sort_algorithms
