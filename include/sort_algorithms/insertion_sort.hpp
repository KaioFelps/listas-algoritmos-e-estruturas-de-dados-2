#pragma once

#include <span>

namespace core::sort_algorithms
{

namespace internal
{

/**
 * Shifts every element from `first` `steps` steps towards `last` (inclusive).
 */
template <typename T> void shift_right(T *first, T *last, size_t steps)
{
  const size_t size = last - first;
  if (!steps || size <= steps) return;

  T *target = last - steps;

  while (target >= first)
  {
    *last = *target;
    last--;
    target--;
  }
}

} // namespace internal

template <typename T> void insertion_sort(std::span<T> vec)
{
  if (vec.size() <= 1) return;

  for (size_t current_element_pos = 1; current_element_pos < vec.size();
       current_element_pos++)
  {
    const auto current_element = vec[current_element_pos];

    size_t first_smaller_element = current_element_pos - 1;
    while (first_smaller_element != 0 &&
           vec[first_smaller_element] >= current_element)
    {
      first_smaller_element--;
    }

    size_t position_to_insert_current_element =
        vec[first_smaller_element] > current_element
            ? first_smaller_element
            : first_smaller_element + 1;

    internal::shift_right(vec.data() + position_to_insert_current_element,
                          vec.data() + current_element_pos, 1);

    vec[position_to_insert_current_element] = current_element;
  }
}

} // namespace core::sort_algorithms
