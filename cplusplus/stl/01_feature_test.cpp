#include "test.hpp"
#include "stl.h"

//=============================================================================
#ifdef __has_include          // 检查 __has_include 是否存在
#if __has_include(<optional>) // 检查标准库
#warning "standard optional"
#include <optional>
#elif __has_include(<experimental/optional>) // 检查实验版本
#warning "experimental optional"
#include <experimental/optional>
#elif __has_include(<boost/optional.hpp>) // 尝试外部库
#warning "boost optional"
#include <boost/optional.hpp>
#else // 完全找不到
#error "Missing <optional>"
#endif
#endif

//=============================================================================
void test_cplusplus_version() {
  std::printf("cplusplus standard version: %ld\n", __cplusplus);
}

//=============================================================================
void use_assume_attribute(int cond_val) {
  [[assume(cond_val > 1)]]; // must use -O option
  if (cond_val > 1) {
    std::printf("cond_val is positive number: %d\n", cond_val);
  } else {
    std::printf("cond_val is negative number: %d\n", cond_val);
  }
}

void test_attribute_1() {
  use_assume_attribute(2);

  // the statement will be cat off.
  use_assume_attribute(0);
}

void test_attribute_2() {
  // this statement will be optimized and else branch that in function
  // use_assume_attribute will be cat off.
  use_assume_attribute(0);

  // because of attribute assume, the next statement will never be executed.
  use_assume_attribute(2);
}

void test_assume_attribute() {
  // TEST(test_attribute_1) statement must came before TEST(test_attribute_2)
  TEST(test_attribute_1); // all the following statements will be cut off.
  // TEST(test_attribute_2);    // all the following statements will be cut off.
}

//=============================================================================
class TestMaybeUnusedClass {
  struct [[maybe_unused]] {
  } S;
  class [[maybe_unused]] {
  } C;
};

// if specify -Wunused-variable, the unused variable with [[maybe_unused]] will
// not be diagnosed
void test_maybe_unused_attribute([[maybe_unused]] int num) {
  TestMaybeUnusedClass TMUC;
  [[maybe_unused]] int local_val = 10;
  [[maybe_unused]] auto add = [](int a, int b) { return a + b; };
}

//=============================================================================
[[deprecated]]
void test_deprecated_attribute() {
  [[deprecated]] int local_val;
}

//=============================================================================
void test_fallthrought_attribute(int choice) {
  int placeholder{1};
  switch (choice) {
  case 0:
  case 1:
    placeholder; // use -Wno-unused-value to screen warning
    // [[fallthrough]];
  case 2:
    placeholder;
  case 3:
    if (true) {
      // [[fallthrough]];
    } else {
      return;
    }
  default:
    placeholder;
  }
}

//=============================================================================
[[nodiscard]]
int get_error_no() {
  return 1;
}

[[nodiscard("error_no shell be handled")]]
int get_error_no(int a = 10) {
  return a;
}

void test_nodiscard_attribute() {
  // get_error_no(); // cause compilation error
  get_error_no(1);
}

//=============================================================================
void test() {
  TEST(test_cplusplus_version);
  // TEST(test_assume_attribute);
  TEST(test_deprecated_attribute);
  TEST(test_maybe_unused_attribute, 10);
  TEST(test_fallthrought_attribute, 2);
}

//=============================================================================
int main(int argc, char *argv[]) { test(); }
