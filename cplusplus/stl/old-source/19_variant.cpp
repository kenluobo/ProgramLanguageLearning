#include "test.h"
#include <variant>

//==============================================================================
void test_variant() {
  std::variant<String, int, double> Var = String("hello world");
  auto RVar = std::get_if<String>(&Var);
  out("RVar<String>: ", *RVar);

  Var = 10;
  auto RVar2 = std::get_if<int>(&Var);
  out("RVar<int>: ", *RVar2);
}
//==============================================================================
void test_variant2() {
  std::variant<StringVector, double> Var = StringVector{"abc", "def"};
  auto RVar = std::get<StringVector>(Var);
  out(getStringVectorAsString(RVar));

  Var = 3.1415926f;
  auto RVar2 = std::get<double>(Var);
  out(RVar2);
}

//==============================================================================
void test() {
  TEST(test_variant);
  TEST(test_variant2);
}

//==============================================================================
int main() { test(); }
