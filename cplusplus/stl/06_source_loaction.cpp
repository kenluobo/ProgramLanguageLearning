#include "utils/test.hpp"
// #include <source_location>
#include <experimental/source_location>

//=====================================================
void test_source_location_1(const std::experimental::source_location src_loc =
                                std::experimental::source_location::current()) {
  out("filename: ", src_loc.file_name());
  out("function name: ", src_loc.function_name());
  out("line: ", src_loc.line());
  out("column: ", src_loc.column());
}

void test_source_location_2() {
  auto src_loc = std::experimental::source_location::current();
  out("filename: ", src_loc.file_name());
  out("function name: ", src_loc.function_name());
  out("line: ", src_loc.line());
  out("column: ", src_loc.column());
}

//=====================================================
void test() {
  TEST(test_source_location_1);
  TEST(test_source_location_2);
}

//=====================================================
int main() { test(); }
