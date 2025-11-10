#pragma once

#include "hash_table.hpp"
#include <cassert>
#include <exception>
#include <list>
#include <memory>
#include <optional>
#include <utility>

namespace core::hash_table
{

namespace internal
{

enum class State
{
  Free,
  Occupied,
  Deleted,
};

}

template <typename V, typename K = size_t>
class OAHashTable : public HashTable<V, K>
{

private:
  class Row
  {
  public:
    std::optional<std::pair<K, V>> element;
    internal::State state;

    Row() : element(std::nullopt), state(internal::State::Free) {}

    bool can_receive_value(K key) const
    {
      using namespace internal;
      if (this->state != State::Occupied) return true;

      assert(this->element.has_value() &&
             "Non-free rows must have element, even if deleted.");

      return this->element->first == key;
    }

    void set_element(K key, V value)
    {
      this->element = std::pair(key, value);
      this->state = internal::State::Occupied;
    }

    void mark_as_deleted() { this->state = internal::State::Deleted; }
  };

  std::unique_ptr<Row[]> internal_list;
  size_t table_size;

  size_t hash(K key) { return key % this->table_size; }

  size_t advance_hash(size_t hash, size_t steps)
  {
    return (hash + steps) % this->table_size;
  }

  std::optional<size_t> find_internal_index_of(K key)
  {
    using namespace internal;
    const auto hash = this->hash(key);

    size_t steps = 0;
    auto probing = this->advance_hash(hash, steps);
    while (probing != hash || steps == 0)
    {
      Row &row = this->internal_list[probing];

      if (row.state == State::Free) break;

      assert(row.element.has_value() &&
             "Non-free rows must have elements, even if `State::Deleted`.");

      if (row.state == State::Occupied && row.element->first == key)
      {
        return probing;
      }

      probing = this->advance_hash(hash, ++steps);
    }

    return std::nullopt;
  }

public:
  OAHashTable(size_t initial_size) : table_size(initial_size)
  {
    this->internal_list = std::make_unique<Row[]>(table_size);
  }

  void insert(K key, V value) noexcept(false) override final
  {
    using namespace internal;
    const auto hash = this->hash(key);

    Row &row = this->internal_list[hash];
    if (row.can_receive_value(key))
    {
      row.set_element(key, value);
      return;
    }

    size_t given_steps = 1;
    size_t probing = this->advance_hash(hash, given_steps);
    while (probing != hash)
    {
      Row &row = this->internal_list[probing];
      if (row.can_receive_value(key)) return row.set_element(key, value);
      probing = this->advance_hash(hash, ++given_steps);
    }

    throw std::bad_alloc();
  }

  std::optional<V> get(K key) override final
  {
    auto internal_index = this->find_internal_index_of(key);
    if (!internal_index.has_value()) return std::nullopt;
    return this->internal_list[*internal_index].element->second;
  }

  void remove(K key) override final
  {
    auto internal_index = this->find_internal_index_of(key);
    if (!internal_index) return;

    Row &row = this->internal_list[*internal_index];
    row.mark_as_deleted();
  }
};

} // namespace core::hash_table
