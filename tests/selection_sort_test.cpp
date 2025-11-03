#include "sort_algorithms.hpp"
#include "utils.hpp"
#include <catch2/catch_all.hpp>

TEST_CASE("it should order vectors", "[selection_sort, external]")
{
  auto unsorted_array = core::utils::generate_random_ints_vector(30, 10, 100);

  // ensures it won't ever accidentally generate an already ordered sequence.
  unsorted_array[0] = 1;
  unsorted_array[1] = 0;
  REQUIRE_FALSE(std::is_sorted(unsorted_array.begin(), unsorted_array.end()));

  core::sort_algorithms::selection_sort<int>(unsorted_array);
  REQUIRE(std::is_sorted(unsorted_array.begin(), unsorted_array.end()));
}

TEST_CASE("it should find the biggest element within a span",
          "[selection_sort, internal]")
{
  using namespace core::sort_algorithms;
  int arr[] = {10, 11, 12, 4, 5, 6};
  auto biggest_el_pos = ___find_biggest_el_pos<int>(arr);
  auto biggest_el = arr[biggest_el_pos];

  REQUIRE(biggest_el == 12);
}

TEST_CASE("it should swap two elements from a vector",
          "[selection_sort, internal]")
{
  using namespace core::sort_algorithms;
  int arr[] = {10, 11, 12, 4, 5, 6};
  int expected_arr[] = {10, 11, 5, 4, 12, 6};

  ___swap<int>(arr, 2, 4);

  REQUIRE(std::ranges::equal(arr, expected_arr));
}
