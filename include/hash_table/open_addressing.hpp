#pragma once

#include "hash_table.hpp"
#include "iostream"
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

    void set_element(K key, V value)
    {
      this->element = std::pair(key, value);
      this->state = internal::State::Occupied;
    }

    void soft_delete()
    {
      this->element = std::nullopt;
      this->state = internal::State::Deleted;
    }

    bool is_occupied() const
    {
      return this->state == internal::State::Occupied;
    }

    bool is_free() const { return this->state == internal::State::Free; }
    bool is_deleted() const { return this->state == internal::State::Deleted; }

    bool is_insertable(const K &key) const
    {
      using namespace internal;

      if (!this->is_occupied()) return true;
      if (this->owns_key(key)) return true;
      return false;
    }

    bool owns_key(const K &key) const
    {
      assert((!this->is_occupied() || this->element.has_value()) &&
             "Occupied rows MUST have an element value.");

      return this->element.has_value() && this->element->first == key;
    }
  };

  std::unique_ptr<Row[]> internal_list;
  size_t internal_list_size;
  size_t _size;
  bool forbid_resize;

  size_t hash(K key) const { return key % this->internal_list_size; }

  size_t advance_hash(size_t hash, size_t steps) const
  {
    return (hash + steps) % this->internal_list_size;
  }

  float load_factor() const
  {
    return (float)this->_size / (float)this->internal_list_size;
  }

  void maybe_resize()
  {
    const auto threshold = this->internal_list_size / 2.0;
    if (this->_size <= threshold || this->forbid_resize) return;
    this->resize(this->internal_list_size * 2);
  }

  void resize(size_t new_internal_list_size)
  {
    auto old_internal_list_size = this->internal_list_size;
    auto old_list = std::move(this->internal_list);

    this->internal_list_size = new_internal_list_size;
    this->internal_list = std::make_unique<Row[]>(new_internal_list_size);
    this->_size = 0;

    for (size_t i = 0; i < old_internal_list_size; i++)
    {
      Row &row = old_list[i];
      if (!row.is_occupied()) continue;
      this->insert(row.element->first, row.element->second);
    }
  }

  std::optional<size_t> find_internal_index_of(K key)
  {
    using namespace internal;
    const auto hash = this->hash(key);

    size_t steps = 0;
    auto probing = this->advance_hash(hash, steps);

    while (steps < this->internal_list_size)
    {
      Row &row = this->internal_list[probing];

      if (row.is_free()) break;
      if (row.is_occupied() && row.owns_key(key)) return probing;
      probing = this->advance_hash(hash, ++steps);
    }

    return std::nullopt;
  }

public:
  OAHashTable(size_t capacity)
      : internal_list_size(capacity), _size(0), forbid_resize(false)
  {
    this->internal_list = std::make_unique<Row[]>(internal_list_size);
  }

  void forbid_resizing() { this->forbid_resize = true; }
  void allow_resizing() { this->forbid_resize = false; }

  size_t size() const override final { return this->_size; }
  size_t capacity() const { return this->internal_list_size; }

  void insert(K key, V value) noexcept(false) override final
  {
    using namespace internal;

    this->maybe_resize();

    const auto hash = this->hash(key);

    Row *best_placement = nullptr;
    bool is_insertion = false;

    size_t given_steps = 0;
    size_t probing = this->advance_hash(hash, given_steps);

    while (given_steps < this->internal_list_size)
    {
      Row &row = this->internal_list[probing];

      // If it's free it means this key haven't ever been inserted before,
      // otherwise it would be deleted.
      if (row.is_free())
      {
        best_placement = &row;
        is_insertion = true;
        break;
      }

      if (row.is_occupied() && row.owns_key(key))
      {
        best_placement = &row;
        is_insertion = false;
        break;
      }

      if (row.is_deleted() && !best_placement)
      {
        best_placement = &row;
        // it is still an insertion, since removal decreases the hash table's
        // size.
        is_insertion = true;
      }

      probing = this->advance_hash(hash, ++given_steps);
    }

    if (!best_placement) throw std::runtime_error("Hash table is full");

    best_placement->set_element(key, value);
    if (is_insertion) this->_size++;
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
    if (row.is_occupied())
    {
      row.soft_delete();
      this->_size--;
    }
  }
};

} // namespace core::hash_table
