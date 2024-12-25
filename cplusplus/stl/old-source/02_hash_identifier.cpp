#include "test.h"

//=============================================================================
#define MAKE_FIXED_NAME_1(prefix, name) (#prefix "_" #name)
#define MAKE_FIXED_NAME_2(prefix, name) (prefix##_##name)

void test_macro_hash_and_hash_hash_identifier() {
  std::printf("CONNECT_STRING: %s\n", CONNECT_STRING(1, 2, 3, 4, 5));
  std::printf("CMAKE_FIXED_NAME_1: %s\n", MAKE_FIXED_NAME_1(hello, world));

  auto MAKE_FIXED_NAME_2(local, var1) = 10;
  std::printf("CMAKE_FIXED_NAME_2: %d\n", local_var1);
}

//=============================================================================
void test() { TEST(test_macro_hash_and_hash_hash_identifier); }

//=============================================================================
int main(int argc, char *argv[]) { test(); }
