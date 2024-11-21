#include "utils/test.hpp"

#include <cstdarg>

//===========================================================
void out_args(const char *msg, ...) {
  va_list args;
  printf("%s\n", msg);

  va_start(args, msg);
  char *curr = NULL;
  while (NULL != (curr = va_arg(args, char *))) {
    printf("%s\n", curr);
  }
  va_end(args);
}

void test_va_args() { out_args("hello", "world", "!"); }

//===========================================================
void test() { TEST(test_va_args); }

//===========================================================
int main() { test(); }
