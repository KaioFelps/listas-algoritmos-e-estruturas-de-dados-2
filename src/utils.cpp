#include "utils.hpp"
#include <iostream>

namespace core::utils
{
std::vector<int> generate_random_ints_vector(size_t size, size_t seed,
                                             size_t max)
{
  auto vec = std::vector<int>();
  vec.reserve(size);

  srand(seed);
  for (size_t i = 0; i < size; i++)
  {
    // Same behavior as val = val > max ? val : val - max.
    vec.push_back(rand() % max);
  }

  return vec;
}

static void shuffle(std::span<int> list, size_t seed)
{
  srand(seed);

  const auto size = list.size();
  if (size <= 1) return;

  for (size_t i = 0; i < size - 1; i++)
  {
    const size_t random_index = i + rand() / (RAND_MAX / (size - i) + 1);
    auto temp = list[random_index];
    list[random_index] = list[i];
    list[i] = temp;
  }
}

std::vector<int> generate_distinct_shuffled_ints_vector(size_t size,
                                                        size_t seed)
{
  auto vec = std::vector<int>();
  vec.reserve(size);

  for (size_t i = 0; i < size; i++)
  {
    vec.push_back(i);
  }

  shuffle(vec, seed);
  return vec;
}
} // namespace core::utils
