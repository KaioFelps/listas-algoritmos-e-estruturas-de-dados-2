#include "trees/binary_search_tree.hpp"

namespace core::trees
{

template <typename K, typename V>
const V *BinarySearchTree<K, V>::get(K key) const
{
  if (!this->root.has_value()) return nullptr;
  const Node &root = *this->root;
  return this->search(key, root);
}

template <typename K, typename V>
V *BinarySearchTree<K, V>::search(K &key, Node &node) const
{
  if (node.key == key) return node.value;
  if (node.key > key)
  {
    if (node.left_node) return this->search(key, *node.left_node);
    return nullptr;
  }

  if (node.right_node) return this->search(key, *node.right_node);
  return nullptr;
}

// template <typename K, typename V>
// void BinarySearchTree<K, V>::insert(K key, V value)
// {
// }

} // namespace core::trees
