#pragma once

#include <iostream>
#include <span>
#include <vector>

namespace core::utils
{
/**
 * Exchanges positions of the elements at the `lhp` and `rhp` positions
 * in `list`.
 */
template <typename T>
void swap(std::span<T> list, const size_t lhp, const size_t rhp)
{
  const auto temporary_value = list[lhp];
  list[lhp] = list[rhp];
  list[rhp] = temporary_value;
}

/**
 * Stringifies and print each element from `vector` in JSON format.
 */
template <typename T>
void print_vector(const std::span<const T> vector, bool breakline = true)
{
  std::cout << "[";

  auto iterator = vector.begin();
  const auto last_element = std::next(vector.end(), -1);
  while (iterator != vector.end())
  {
    std::cout << std::to_string(*iterator);
    if (iterator != last_element) std::cout << ", ";
    iterator = std::next(iterator);
  }

  std::cout << "]";
  if (breakline) std::cout << "\n";
}

std::vector<int> generate_random_ints_vector(size_t size, size_t seed,
                                             size_t max);

std::vector<int> generate_distinct_shuffled_ints_vector(size_t size,
                                                        size_t seed);
} // namespace core::utils
