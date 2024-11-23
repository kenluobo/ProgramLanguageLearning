#include "stl.h"
#include "test.hpp"

//=================================================
void test_initializer_list() {
  std::initializer_list<int> nums{1, 2, 3, 4, 5};
  out(nums.size());

  std::for_each(nums.begin(), nums.end(), [](int n) { std::cout << n << " "; });
  std::cout << "\n";
}

//=================================================
void test() { TEST(test_initializer_list); }

//=================================================
int main() { test(); }
