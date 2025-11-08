#pragma once

#include <span>

namespace core::sort_algorithms::internal
{

template <typename T>
void swap(std::span<T> vector, size_t left_hand_el_pos,
          size_t right_hand_el_pos)
{
  auto tmp = vector[left_hand_el_pos];
  vector[left_hand_el_pos] = vector[right_hand_el_pos];
  vector[right_hand_el_pos] = tmp;
}

} // namespace core::sort_algorithms::internal
