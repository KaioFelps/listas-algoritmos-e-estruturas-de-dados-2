#pragma once

#include "utils.hpp"
#include <memory>
#include <stddef.h>

namespace core::sort_algorithms
{
void merge_sort(int *arr, int p, int r);

/// Copies `subvector_size` elements from `vector` to a new heap-allocated
/// subvector.
///
/// It does not face `vector` as a simple array pointer, but as a pointer
/// to the first element of a dynamic array from where it should begin copying.
/// the elements. I.e., `vector` may be a pointer to the third element
/// of some arbitrary array, and this function will copy `subvector_size`
/// elements starting from it.
///
/// It won't check for boundaries nor throw any exceptions. Not ensuring
/// `vector + subvector_size - 1` is still a valid position from `vector` will
/// cause undefined behavior.
///
/// # Example
/// ```cpp
/// using namespace core::sort_algorithms;
/// const int arr[] = {1, 2, 3, 4, 5, 6};
/// const auto subset = ___copy_to_subvector(arr + 1, 3);
///
/// core::utils::print_vector(subset, false);
/// // "[2, 3, 4]"
/// ```
template <typename T>
std::unique_ptr<T[]> ___copy_to_subvector(const T *vector,
                                          const size_t subvector_size)
{
  auto subvector = std::unique_ptr<T[]>(new T[subvector_size]);

  for (size_t i = 0; i < subvector_size; i++)
  {
    subvector[i] = *vector;
    vector = vector + 1;
  }

  return subvector;
}

template <typename T> struct ___InterleaveArgs
{
  T *target_vector;
  const std::unique_ptr<T[]> right_subvec;
  const std::unique_ptr<T[]> left_subvec;
  size_t left_subvector_size;
  size_t right_subvector_size;
  size_t vector_first_element_pos;
  size_t vector_last_element_pos;
  size_t vector_central_element_pos;
};

template <typename T> void ___interleave(___InterleaveArgs<T> args)
{
  size_t left_cursor = 0, right_cursor = 0,
         cursor = args.vector_first_element_pos;

  for (; cursor <= args.vector_last_element_pos; cursor++)
  {
    const auto some_subvector_has_reached_end =
        left_cursor == args.left_subvector_size ||
        right_cursor == args.right_subvector_size;

    if (some_subvector_has_reached_end) break;

    if (args.left_subvec[left_cursor] <= args.right_subvec[right_cursor])
    {
      args.target_vector[cursor] = args.left_subvec[left_cursor++];
      continue;
    }

    args.target_vector[cursor] = args.right_subvec[right_cursor++];
  }

  const auto left_subvector_is_done = left_cursor == args.left_subvector_size;
  if (left_subvector_is_done)
  {
    for (; cursor <= args.vector_last_element_pos; cursor++)
    {
      args.target_vector[cursor] = args.right_subvec[right_cursor++];
    }
    return;
  }

  for (; cursor <= args.vector_last_element_pos; cursor++)
  {
    args.target_vector[cursor] = args.left_subvec[left_cursor++];
  }
}

/**
 * @param subvector A heap-allocated C array of `T`.
 * @param first_element_pos The index of subvector's first element (not
 * necessarily `0`).
 * @param central_element_pos The index of subvector's central element. If
 * even subvector, the position of the last element from the first half of
 * it.
 * @param last_element_pos The index of the subvector's last element (not
 * necessarily `subvector.size() - 1`).
 */
template <typename T>
void ___merge(T *subvector, const size_t first_element_pos,
              const size_t central_element_pos, const size_t last_element_pos)
{
  // The math for getting any vector range size is
  // size = right_limit - left_limit + 1.
  //
  // The first element index from the right subvector is
  // central_element_pos + 1. Therefore, the formula would be:
  // size = last_element_pos - (central_element_pos + 1) + 1,
  //      = last_element_pos - central_element_pos -1 + 1
  //      = last_element_pos - central_element_pos

  const auto left_subvector_size = central_element_pos - first_element_pos + 1;
  const auto right_subvector_size = last_element_pos - central_element_pos;

  auto left_subvec = ___copy_to_subvector<T>(subvector, left_subvector_size);
  auto right_subvec = ___copy_to_subvector<T>(
      subvector + central_element_pos + 1, right_subvector_size);

  ___interleave(___InterleaveArgs<int>{
      .target_vector = subvector,
      .vector_central_element_pos = central_element_pos,
      .vector_first_element_pos = first_element_pos,
      .vector_last_element_pos = last_element_pos,
      .left_subvec = std::move(left_subvec),
      .left_subvector_size = left_subvector_size,
      .right_subvec = std::move(right_subvec),
      .right_subvector_size = right_subvector_size,
  });
}

/**
 * An implementation of Merge Sort with no sentinels usage,
 * making it appliable to complex — but comparable — types.
 */
template <typename T> void merge_sort() {}
} // namespace core::sort_algorithms
