#include "stl.h"
#include "test.hpp"

struct TrivialClass {
  int a;
  float f;
};

struct NonTrivialClass {
  int a;
  NonTrivialClass() { out("NonTrivialClass ctor ", __func__); }
  ~NonTrivialClass() { out("NonTrivialClass dtor ", __func__); }
};

void test_placement_new_1() {
  unsigned char buffer[sizeof(TrivialClass)];
  memset(buffer, 0, sizeof(TrivialClass));
  out("buffer address: ", static_cast<const void *>(buffer));

  TrivialClass *p_tc = new (buffer) TrivialClass();
  out("TrivialClass p_tc address: ", p_tc);
}

void test_placement_new_2() {
  unsigned char buffer[sizeof(NonTrivialClass)];
  memset(buffer, 0, sizeof(NonTrivialClass));
  out("buffer address: ", static_cast<const void *>(buffer));

  NonTrivialClass *p_ntc = new (buffer) NonTrivialClass();
  out("TrivialClass p_tc address: ", p_ntc);
}

//=====================================================
void test() {
  TEST(test_placement_new_1);
  TEST(test_placement_new_2);
}

//=====================================================
int main() { test(); }
