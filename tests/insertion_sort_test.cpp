#include "sort_algorithms/insertion_sort.hpp"
#include "utils.hpp"
#include <catch2/catch_all.hpp>

TEST_CASE("it should order vectors", "[insertion_sort, external]")
{
  SECTION("set (no repeated elements)")
  {
    auto vector = core::utils::generate_distinct_shuffled_ints_vector(100, 200);
    core::sort_algorithms::insertion_sort<int>(vector);
    REQUIRE(std::ranges::is_sorted(vector));
  }

  SECTION("random vector (with repeated elements)")
  {
    auto vector = core::utils::generate_random_ints_vector(100, 100, 200);
    core::sort_algorithms::insertion_sort<int>(vector);
    REQUIRE(std::ranges::is_sorted(vector));
  }
}

TEST_CASE("it should correctly shift elements `steps` to the right",
          "[insertion_sort, internal]")
{
  using core::sort_algorithms::internal::shift_right;
  auto vec = std::vector{3, 4, 5, 6, 1};
  const auto expected = std::span<const int>({3, 3, 4, 5, 6});

  const size_t position_of_el_1 = 4;
  shift_right(vec.data(), vec.data() + position_of_el_1, 1);
  REQUIRE(std::ranges::equal(vec, expected));
}
