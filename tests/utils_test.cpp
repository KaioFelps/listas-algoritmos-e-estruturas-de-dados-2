#include "utils.hpp"
#include <catch2/catch_all.hpp>
#include <iostream>
#include <span>

TEST_CASE("print_vector prints a JSON array", "[print_vector]")
{
  const int array[] = {20, 50, 10, 30, 60, 80};
  auto print_with_newline = std::stringstream();
  auto print_without_newline = std::stringstream();

  auto cout_buffer = std::cout.rdbuf(print_with_newline.rdbuf());
  core::utils::print_vector<int>(array);

  std::cout.rdbuf(print_without_newline.rdbuf());
  core::utils::print_vector<int>(array, false);

  std::cout.rdbuf(cout_buffer);

  REQUIRE(print_with_newline.str() == "[20, 50, 10, 30, 60, 80]\n");
  REQUIRE(print_without_newline.str() == "[20, 50, 10, 30, 60, 80]");
}
