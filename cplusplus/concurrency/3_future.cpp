#include "utils.h"

//==============================================================================
int calculate_in_the_background(int num) {
  out_and_wait<3>(__func__);
  return num;
}

int calculate_in_the_front(int num) {
  out_and_wait<5>(__func__);
  return num;
}

//==============================================================================
void test_future_default() {
  std::future<int> b_ret = std::async(calculate_in_the_background, 10);
  int f_ret = calculate_in_the_front(20);

  out("background result: ", std::to_string(b_ret.get()));
  out("front result: ", std::to_string(f_ret));
}

//==============================================================================
void test_future_async() {
  std::future<int> b_ret =
      std::async(std::launch::async, calculate_in_the_background, 10);
  int f_ret = calculate_in_the_front(20);

  out("background result: ", std::to_string(b_ret.get()));
  out("front result: ", std::to_string(f_ret));
}

//==============================================================================
void test_future_defered() {
  std::future<int> b_ret =
      std::async(std::launch::deferred, calculate_in_the_background, 10);
  int f_ret = calculate_in_the_front(20);

  out("background result: ", std::to_string(b_ret.get()));
  out("front result: ", std::to_string(f_ret));
}

//==============================================================================
int main() { test_future_default(); }
