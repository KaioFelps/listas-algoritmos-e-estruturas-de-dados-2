#include "catch2/catch_all.hpp"
#include "hash_table.hpp"
#include <utility>
#include <vector>

TEST_CASE("it should be able to correctly insert and get elements",
          "[OAHashTable, external]")
{
  std::vector<std::pair<size_t, int>> pairs = {
      std::pair(0, 1),  std::pair(3, 2), std::pair(11, 3),
      std::pair(12, 4), std::pair(6, 5), std::pair(14, 6)};

  auto hash_table = core::hash_table::OAHashTable<int>(10);

  for (const auto &pair : pairs)
  {
    REQUIRE_NOTHROW(hash_table.insert(pair.first, pair.second));
  }
  REQUIRE_NOTHROW(hash_table.insert(14, 3));

  for (const auto &pair : pairs)
  {
    auto element = hash_table.get(pair.first);
    REQUIRE(element.has_value());

    if (pair.first == 14)
    {
      REQUIRE(*element == 3);
    }
    else
    {
      REQUIRE(*element == pair.second);
    }
  }
}

TEST_CASE("it should return `nullopt`s when trying to get a non-existing value",
          "[OAHashTable, external]")
{
  auto hash_table = core::hash_table::OAHashTable<int>(10);

  for (size_t key = 0; key <= 100; key++)
  {
    auto element = hash_table.get(key);
    REQUIRE_FALSE(element.has_value());
  }
}

TEST_CASE("it should remove a value by key", "[OAHashTable, external]")
{
  auto hash_table = core::hash_table::OAHashTable<int>(10);

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

TEST_CASE("it should not assumpt the correct key have been deleted because a "
          "collided one have been before it reached the actual target",
          "[OAHashTable, internal]")
{
  auto hash_table = core::hash_table::OAHashTable<int>(10);
  hash_table.insert(10, 1);
  hash_table.insert(100, 2);

  hash_table.remove(10);
  hash_table.remove(100);

  REQUIRE_FALSE(hash_table.get(10).has_value());
  REQUIRE_FALSE(hash_table.get(100).has_value());
}

TEST_CASE("it should correctly handle collisions as long as there is space in "
          "the table",
          "[OAHashTable, internal]")
{
  std::vector<std::pair<size_t, int>> pairs = {
      std::pair(7, 1),  std::pair(14, 2), std::pair(21, 3), std::pair(28, 4),
      std::pair(35, 4), std::pair(42, 5), std::pair(49, 6)};

  auto hash_table = core::hash_table::OAHashTable<int>(7);

  for (const auto &pair : pairs)
  {
    REQUIRE_NOTHROW(hash_table.insert(pair.first, pair.second));
  }

  SECTION("it should find every inserted key even though they had collided")
  {
    for (const auto &pair : pairs)
    {
      REQUIRE(hash_table.get(pair.first).has_value());
    }
  }
}

TEST_CASE("it should correctly forward the value until list is empty in an "
          "attempt to insert a key-value pair",
          "[OAHashTable, internal]")
{
  std::vector<std::pair<size_t, int>> pairs = {
      std::pair(7, 1),  std::pair(14, 2), std::pair(21, 3), std::pair(28, 4),
      std::pair(35, 4), std::pair(42, 5), std::pair(49, 6)};

  auto hash_table = core::hash_table::OAHashTable<int>(7);

  for (const auto &pair : pairs)
  {
    REQUIRE_NOTHROW(hash_table.insert(pair.first, pair.second));
  }

  SECTION("it should find every inserted key even though they had collided")
  {
    for (const auto &pair : pairs)
    {
      REQUIRE(hash_table.get(pair.first).has_value());
    }
  }

  SECTION("it should throw an exception when trying to insert new keys into a"
          "full hash table")
  {
    REQUIRE_THROWS_AS(hash_table.insert(56, 10), std::bad_alloc);
  }
}

TEST_CASE("it should replace an already existing key",
          "[OAHashTable, internal]")
{
  auto hash_table = core::hash_table::OAHashTable<int>(7);

  const auto key = 0;
  hash_table.insert(key, 100);

  const auto new_element = 20;
  hash_table.insert(key, new_element);
  auto just_added_element = hash_table.get(key);

  REQUIRE(just_added_element.has_value());
  REQUIRE(*just_added_element == new_element);
}
