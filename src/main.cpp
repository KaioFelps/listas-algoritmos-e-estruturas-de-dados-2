#include "hash_table.hpp"
#include "utils.hpp"
#include <iostream>

int main(/* int argc, char **argv */)
{
  auto hash_table = core::hash_table::SCHashTable<int>(7);

  hash_table.insert(0, 1);
  hash_table.insert(3, 2);
  hash_table.insert(11, 3);
  hash_table.insert(12, 4);
  hash_table.insert(6, 5);
  hash_table.insert(14, 6);

  hash_table.remove(14);
  hash_table.remove(14);

  for (size_t i = 0; i < 15; i++)
  {
    std::cout << "hash_table[" << i << "] = ";
    auto value = hash_table.get(i);

    if (value)
    {
      std::cout << *value << ";\n";
      continue;
    }

    std::cout << "undefined;\n";
  }

  return 0;
}
