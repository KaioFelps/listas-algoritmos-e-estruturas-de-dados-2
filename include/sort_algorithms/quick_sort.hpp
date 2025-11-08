#pragma once

#include "sort_algorithms/utils.hpp"
#include <span>

namespace core::sort_algorithms::internal
{

/**
 * The Lomuto Partition Algorithm ensures that every element from `vec`
 * that is smaller than `pivot` is placed on its left and the bigger ones
 * on its right.
 *
 * @param vec The vector to partition.
 * @param pivot_pos The position of the choosen `pivot`.
 * @returns The new `pivot`s position.
 */
template <typename T> size_t partition(std::span<T> vec, size_t pivot_pos)
{
  const auto last_element_pos = vec.size() - 1;
  if (pivot_pos != last_element_pos)
  {
    internal::swap(vec, pivot_pos, last_element_pos);
    pivot_pos = last_element_pos;
  }

  auto pivot = vec[pivot_pos];

  /**
   * The border who separates those elements smaller than the pivot from the
   * bigger ones
   */
  size_t border_cursor = 0;

  for (size_t current_el_cursor = 0; current_el_cursor < pivot_pos;
       current_el_cursor++)
  {
    auto &element = vec[current_el_cursor];

    if (element > pivot) continue;

    internal::swap(vec, current_el_cursor, border_cursor);
    border_cursor++;
  }

  internal::swap(vec, pivot_pos, border_cursor);
  return border_cursor;
}

typedef struct
{
  size_t offset;
  size_t count;
} QuickSortSubvectorRange;

typedef struct
{
  QuickSortSubvectorRange left;
  QuickSortSubvectorRange right;
} QuickSortSubvectorsRanges;

QuickSortSubvectorsRanges calculate_subvectors(size_t vec_size,
                                               size_t pivot_pos)
{
  auto left_range = QuickSortSubvectorRange{.offset = 0, .count = pivot_pos};

  auto right_range = QuickSortSubvectorRange{
      .count = 0,
      .offset = pivot_pos + 1,
  };

  right_range.count = vec_size - right_range.offset;

  return QuickSortSubvectorsRanges{.left = left_range, .right = right_range};
}

} // namespace core::sort_algorithms::internal

namespace core::sort_algorithms
{

template <typename T> void quick_sort(std::span<T> vec, size_t pivot_pos)
{
  using namespace internal;
  if (vec.size() <= 1) return;

  pivot_pos = partition(vec, pivot_pos);

  auto subvecs = calculate_subvectors(vec.size(), pivot_pos);

  auto left_subvec = vec.subspan(subvecs.left.offset, subvecs.left.count);
  const auto left_subvec_pivot = subvecs.left.count - 1;
  quick_sort(left_subvec, left_subvec_pivot);

  auto right_subvec = vec.subspan(subvecs.right.offset, subvecs.right.count);
  const auto right_subvec_pivot = subvecs.right.count - 1;
  quick_sort(right_subvec, right_subvec_pivot);
}

template <typename T> void quick_sort(std::span<T> vec)
{
  quick_sort(vec, vec.size() > 0 ? vec.size() - 1 : 0);
}

} // namespace core::sort_algorithms
