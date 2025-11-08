#include "sort_algorithms/utils.hpp"
#include <catch2/catch_all.hpp>

TEST_CASE("it should swap two elements from a vector",
          "[sort_algorithms, internal]")
{
  using namespace core::sort_algorithms::internal;
  int arr[] = {10, 11, 12, 4, 5, 6};
  int expected_arr[] = {10, 11, 5, 4, 12, 6};

  swap<int>(arr, 2, 4);

  REQUIRE(std::ranges::equal(arr, expected_arr));
}
