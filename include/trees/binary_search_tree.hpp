#pragma once

#include <algorithm>
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

  size_t height(Node &node)
  {
    size_t counter = 1;
    size_t left_height = 0;
    size_t right_height = 0;

    if (node.left_node.has_value())
    {
      left_height = height(*node.left_node.value());
    }

    if (node.right_node.has_value())
    {
      right_height = height(*node.right_node.value());
    }

    counter += std::max(left_height, right_height);
    return counter;
  }

public:
  void insert(K key, V value);
  void remove(K key);
  const V *get(K key) const;
  /**
   * Counts nodes from this tree instance.
   */
  size_t count() const {}
  /**
   * Gets the height of the tree (i.e., the deepness of its deepest node).
   */
  size_t height() const
  {
    if (!this->root.has_value()) return 0;
    return height(*this->root.value());
  }
};

} // namespace core::trees
