#include "sort_algorithms/quick_sort.hpp"
#include "utils.hpp"
#include <algorithm>
#include <catch2/catch_all.hpp>

using namespace core::sort_algorithms;

TEST_CASE("it should ensure elements on pivot's left are smaller than it"
          "and those on its right are bigger than it",
          "[quick_sort, internal]")
{
  auto input_vec = core::utils::generate_random_ints_vector(100, 0, 200);
  const auto pivot_pos = input_vec.size() - 1;
  const auto pivot = input_vec[pivot_pos];

  const size_t new_pivots_pos = ___partition<int>(input_vec, pivot_pos);

  REQUIRE(input_vec[new_pivots_pos] == pivot);

  for (size_t i = 0; i < new_pivots_pos; i++)
  {
    const auto &element = input_vec[i];
    REQUIRE(element <= pivot);
  }

  for (size_t i = input_vec.size() - 1; i > new_pivots_pos; i--)
  {
    const auto &element = input_vec[i];
    REQUIRE(element > pivot);
  }
}
