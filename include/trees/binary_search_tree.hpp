#pragma once

#include <memory>
#include <optional>

namespace core::trees
{

template <typename K, typename V> class BinarySearchTree
{
private:
  class Node
  {
  private:
    std::optional<std::unique_ptr<Node>> left_node;
    std::optional<std::unique_ptr<Node>> right_node;
    K key;
    V value;
  };

  std::optional<std::unique_ptr<Node>> root;
  V *search(K &key, Node &node) const;

public:
  void insert(K key, V value);
  void remove(K key);
  const V *get(K key) const;
};

} // namespace core::trees
