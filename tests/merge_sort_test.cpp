#include "sort_algorithms/merge_sort.hpp"
#include "utils.hpp"
#include <catch2/catch_all.hpp>
#include <span>

TEST_CASE("it should order vectors",
          "[merge_sort, iteratively_merge_sort, external]")
{
  auto unsorted_array = core::utils::generate_random_ints_vector(30, 10, 100);

  // ensures it won't ever accidentally generate an already ordered sequence.
  unsorted_array[0] = 1;
  unsorted_array[1] = 0;
  REQUIRE_FALSE(std::is_sorted(unsorted_array.begin(), unsorted_array.end()));

  SECTION("recursively")
  {
    auto array_copy = unsorted_array;
    core::sort_algorithms::merge_sort<int>(array_copy);
    REQUIRE(std::is_sorted(array_copy.begin(), array_copy.end()));
  }

  SECTION("iteratively")
  {
    auto array_copy = unsorted_array;
    core::sort_algorithms::iteratively_merge_sort<int>(array_copy);

    REQUIRE(std::is_sorted(array_copy.begin(), array_copy.end()));
  }
}

TEST_CASE("it should create subvectors from some window of a vector",
          "[merge_sort, ___copy_to_subvector, internal]")
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

TEST_CASE("it should correctly interleave the sorted subvectors",
          "[merge_sort, ___interleave, internal]")
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

  REQUIRE(std::ranges::equal(initial_vector, std::vector{4, 5, 6, 10, 11, 12}));
}

TEST_CASE("it should correctly sort and merge an array",
          "[merge_sort, ___merge, internal]")
{
  using namespace core::sort_algorithms;

  SECTION("2-sized vectors")
  {
    SECTION("is unordered")
    {
      std::vector<int> vec = {2, 1};
      ___merge(vec.data(), 0, 0, 1);
      REQUIRE(std::ranges::equal(vec, std::span<const int>({1, 2})));
    }

    SECTION("is ordered")
    {
      std::vector<int> vec = {1, 2};
      ___merge(vec.data(), 0, 0, 1);
      REQUIRE(std::ranges::equal(vec, std::span<const int>({1, 2})));
    }
  }

  SECTION("3-sized vectors")
  {
    SECTION("is unordered")
    {
      std::vector<int> vec = {2, 0, 1};

      ___merge(vec.data(), 0, 0, 1);
      ___merge(vec.data(), 1, 1, 2);
      ___merge(vec.data(), 0, 1, 2);

      REQUIRE(std::ranges::equal(vec, std::span<const int>({0, 1, 2})));
    }

    SECTION("is ordered")
    {
      std::vector<int> vec = {0, 1, 2};

      ___merge(vec.data(), 0, 0, 1);
      ___merge(vec.data(), 1, 1, 2);
      ___merge(vec.data(), 0, 1, 2);

      REQUIRE(std::ranges::equal(vec, std::span<const int>({0, 1, 2})));
    }
  }
}

TEST_CASE("it should count the inversions occurrence in the given vector",
          "[merge_sort, external, internal, topic3:ex1]")
{
  int arr[5] = {3, 1, 2, 5, 4};
  int arr_2[3] = {3, 2, 1};

  uint8_t expected_inversions_count = 3;

  SECTION("recursively")
  {
    int copy_5_sized[5];
    int copy_3_sized[3];

    std::copy(arr, arr + 5, copy_5_sized);
    std::copy(arr_2, arr_2 + 3, copy_3_sized);

    auto metadata_1 = core::sort_algorithms::merge_sort<int>(copy_5_sized);
    auto metadata_2 = core::sort_algorithms::merge_sort<int>(copy_3_sized);
    REQUIRE(metadata_1.inversions_count == expected_inversions_count);
    REQUIRE(metadata_2.inversions_count == expected_inversions_count);
  }

  SECTION("iteratively")
  {
    using core::sort_algorithms::iteratively_merge_sort;
    int copy_5_sized[5];
    int copy_3_sized[3];

    std::copy(arr, arr + 5, copy_5_sized);
    std::copy(arr_2, arr_2 + 3, copy_3_sized);

    auto metadata_1 = iteratively_merge_sort<int>(copy_5_sized);
    auto metadata_2 = iteratively_merge_sort<int>(copy_3_sized);
    REQUIRE(metadata_1.inversions_count == expected_inversions_count);
    REQUIRE(metadata_2.inversions_count == expected_inversions_count);
  }
}
