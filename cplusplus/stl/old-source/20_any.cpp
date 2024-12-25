#include "test.h"

//==============================================================================
void test_any() {
  std::any Any = 10;
  out("Any type name: ", Any.type().name());
  auto PA = std::any_cast<int>(&Any);
  out("Any value(int): ", nullptr == PA ? "nullptr" : std::to_string(*PA));

  auto PStr = std::any_cast<String>(&Any);
  out("Any value(String): ", nullptr == PStr ? "nullptr" : *PStr);

  Any.reset();
  out("Any value(after reset): ",
      Any.has_value() ? "has value" : "has no value");
}

//==============================================================================
void test() { TEST(test_any); }

//==============================================================================
int main() { test(); }
