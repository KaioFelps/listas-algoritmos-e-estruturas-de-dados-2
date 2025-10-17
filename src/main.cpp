#include "utils.hpp"

int main(/* int argc, char **argv */)
{
  int teste[] = {1, 2, 3, 4, 5, 10, 20};
  core::utils::print_vector<int>(teste);
  core::utils::swap<int>(teste, 2, 3);
  core::utils::print_vector<int>(teste);

  auto foo = core::utils::generate_random_ints_vector(10, 999, 10000);
  core::utils::print_vector<int>(foo);

  auto bar = core::utils::generate_distinct_shuffled_ints_vector(10, 999);
  core::utils::print_vector<int>(bar);

  return 0;
}
