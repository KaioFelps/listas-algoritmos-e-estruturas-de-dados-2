#include "sort_algorithms/merge_sort.hpp"
#include <catch2/catch_all.hpp>
#include <span>

TEST_CASE("it should create subvectors from some window of a vector",
          "[internal]")
{
  using namespace core::sort_algorithms;
  const int full_array[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  const size_t subvector_size = 3;

  SECTION("starting from index 0")
  {
    auto subvector = ___copy_to_subvector(full_array, subvector_size);
    auto subvector_as_span =
        std::span<const int>(subvector.get(), subvector_size);

    auto expected = std::span<const int>({1, 2, 3});
    auto unexpected = std::span<const int>({2, 3, 4});

    REQUIRE(std::ranges::equal(subvector_as_span, expected));
    REQUIRE_FALSE(std::ranges::equal(subvector_as_span, unexpected));
  }

  SECTION("starting from some arbitrary index")
  {
    auto subvector = ___copy_to_subvector(full_array + 3, subvector_size);
    auto subvector_as_span =
        std::span<const int>(subvector.get(), subvector_size);

    auto expected = std::span<const int>({4, 5, 6});
    auto unexpected = std::span<const int>({3, 4, 5});

    REQUIRE(std::ranges::equal(subvector_as_span, expected));
    REQUIRE_FALSE(std::ranges::equal(subvector_as_span, unexpected));
  }
}

TEST_CASE("it should correctly interleave the sorted subvectors", "[internal]")
{
  using namespace core::sort_algorithms;
  int initial_vector[] = {10, 11, 12, 4, 5, 6};

  ___interleave(___InterleaveArgs<int>{
      .left_subvec = ___copy_to_subvector(initial_vector, 3),
      .right_subvec = ___copy_to_subvector(initial_vector + 3, 3),
      .left_subvector_size = 3,
      .right_subvector_size = 3,
      .target_vector = initial_vector,
      .vector_central_element_pos = 2,
      .vector_last_element_pos = 5,
      .vector_first_element_pos = 0,
  });

  std::cout << std::ranges::equal(initial_vector,
                                  std::vector{4, 5, 6, 10, 11, 12});

  REQUIRE(std::ranges::equal(initial_vector, std::vector{4, 5, 6, 10, 11, 12}));
}
