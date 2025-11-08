#include "sort_algorithms/quick_sort.hpp"
#include "utils.hpp"
#include <algorithm>
#include <catch2/catch_all.hpp>

using namespace core::sort_algorithms;
using namespace internal;

TEST_CASE("it should sort a span-representable list")
{
  auto input_vec = core::utils::generate_random_ints_vector(100, 0, 200);
  quick_sort<int>(input_vec);
  REQUIRE(std::is_sorted(input_vec.begin(), input_vec.end()));
}

TEST_CASE("it should ensure elements on pivot's left are smaller than it"
          "and those on its right are bigger than it",
          "[quick_sort, internal]")
{
  auto input_vec = core::utils::generate_random_ints_vector(100, 0, 200);
  const auto pivot_pos = input_vec.size() - 1;
  const auto pivot = input_vec[pivot_pos];

  const size_t new_pivots_pos = partition<int>(input_vec, pivot_pos);

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

TEST_CASE("it should calculate the correct ranges for the subvectors on "
          "pivot's sides",
          "[quick_sort, internal]")
{
  SECTION("pivot is in the center")
  {
    size_t vec_size = 10;
    size_t pivot_pos = 4;

    auto ranges = calculate_subvectors(vec_size, pivot_pos);

    REQUIRE(ranges.left.offset == 0);
    REQUIRE(ranges.left.count == 4);

    REQUIRE(ranges.right.offset == 5);
    REQUIRE(ranges.right.count == 5);
  }

  SECTION("pivot is the first element")
  {
    size_t vec_size = 10;
    size_t pivot_pos = 0;
    auto ranges = calculate_subvectors(vec_size, pivot_pos);

    REQUIRE(ranges.left.count == 0);
    REQUIRE(ranges.right.count == 9);
  }

  SECTION("pivot is the last element")
  {
    size_t vec_size = 10;
    size_t pivot_pos = 9;
    auto ranges = calculate_subvectors(vec_size, pivot_pos);

    REQUIRE(ranges.left.count == 9);
    REQUIRE(ranges.right.count == 0);
  }

  SECTION("pivot is the only element")
  {
    size_t vec_size = 1;
    size_t pivot_pos = 0;
    auto ranges = calculate_subvectors(vec_size, pivot_pos);

    REQUIRE(ranges.left.count == 0);
    REQUIRE(ranges.right.count == 0);
  }
}
