#pragma once

#include <algorithm>
#include <list>
#include <memory>
#include <optional>
#include <stdlib.h>
#include <string>
#include <utility>

namespace core::hash_table
{

template <typename V, typename K = size_t> class SCHashTable
{
private:
  size_t table_size;
  size_t _size;
  std::unique_ptr<std::list<std::pair<K, V>>[]> internal_list;

  size_t hash(K key) { return key % this->table_size; }

public:
  SCHashTable(size_t initial_size) : table_size(initial_size), _size(0)
  {

    this->internal_list =
        std::make_unique<std::list<std::pair<K, V>>[]>(initial_size);
  }

  virtual size_t size() const { return this->_size; }

  void insert(K key, V value)
  {
    auto hash = this->hash(key);
    std::list<std::pair<K, V>> &bucket = this->internal_list[hash];
    auto pair_it =
        std::find_if(bucket.begin(), bucket.end(),
                     [&key](const auto &pair) { return pair.first == key; });

    if (pair_it != bucket.end())
    {
      (*pair_it).second = value;
      return;
    }

    bucket.push_back(std::pair(key, value));
    this->_size++;
  }

  std::optional<V> get(K key)
  {
    auto h = this->hash(key);

    std::list<std::pair<K, V>> &bucket = this->internal_list[h];
    auto value_iterator = std::find_if(bucket.begin(), bucket.end(),
                                       [&key](const std::pair<K, V> &pair)
                                       { return pair.first == key; });

    if (value_iterator == bucket.end()) return std::nullopt;
    return (*value_iterator).second;
  }

  void remove(K key)
  {
    auto hash = this->hash(key);
    std::list<std::pair<K, V>> &bucket = this->internal_list[hash];
    const auto removed_elements = bucket.remove_if(
        [&key](const auto &value) { return value.first == key; });

    this->_size -= removed_elements;
  }
};

} // namespace core::hash_table
