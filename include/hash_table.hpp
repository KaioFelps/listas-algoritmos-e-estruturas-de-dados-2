#pragma once

#include <optional>

namespace core::hash_table
{

template <typename V, typename K> class HashTable
{
  virtual void insert(K key, V value) noexcept(false) = 0;
  virtual std::optional<V> get(K key) = 0;
  virtual void remove(K key) = 0;
};

} // namespace core::hash_table

#include "hash_table/open_addressing.hpp"
#include "hash_table/separate_chaining.hpp"
