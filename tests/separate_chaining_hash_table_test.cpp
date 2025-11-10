#include "catch2/catch_all.hpp"
#include "hash_table.hpp"
#include <utility>
#include <vector>

TEST_CASE("it should be able to correctly insert and get elements",
          "[SCHashTable, external]")
{
  std::vector<std::pair<size_t, int>> pairs = {
      std::pair(0, 1),  std::pair(3, 2), std::pair(11, 3), std::pair(12, 4),
      std::pair(12, 4), std::pair(6, 5), std::pair(14, 6)};

  auto hash_table = core::hash_table::SCHashTable<int>(10);

  for (const auto &pair : pairs)
  {
    REQUIRE_NOTHROW(hash_table.insert(pair.first, pair.second));
  }

  for (const auto &pair : pairs)
  {
    auto element = hash_table.get(pair.first);
    REQUIRE(element.has_value());
    REQUIRE(*element == pair.second);
  }
}

TEST_CASE("it should return `nullopt`s when trying to get a non-existing value",
          "[SCHashTable, external]")
{
  auto hash_table = core::hash_table::SCHashTable<int>(10);

  for (size_t key = 0; key <= 100; key++)
  {
    auto element = hash_table.get(key);
    REQUIRE_FALSE(element.has_value());
  }
}

TEST_CASE("it should remove a value by key", "[SCHashTable, external]")
{
  auto hash_table = core::hash_table::SCHashTable<int>(10);

  std::vector<std::pair<size_t, int>> pairs = {
      std::pair(0, 1),  std::pair(3, 2), std::pair(11, 3), std::pair(12, 4),
      std::pair(12, 4), std::pair(6, 5), std::pair(14, 6)};

  for (const auto &pair : pairs)
  {
    REQUIRE_NOTHROW(hash_table.insert(pair.first, pair.second));
  }

  for (const auto &pair : pairs)
  {
    hash_table.remove(pair.first);
  }

  for (size_t key = 0; key <= 100; key++)
  {
    auto element = hash_table.get(key);
    REQUIRE_FALSE(element.has_value());
  }
}
