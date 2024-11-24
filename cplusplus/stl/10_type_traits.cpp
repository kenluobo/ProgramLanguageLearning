#include "stl.h"
#include "test.h"

//=============================================================
#define IS_SAME(TY1, TY2)                                                      \
  do {                                                                         \
    std::cout << std::boolalpha;                                               \
    out("std::is_same<", #TY1, ", ", #TY2, ">::value ",                        \
        std::is_same<TY1, TY2>::value);                                        \
  } while (0);

#define IS_SAME_REMOVE_CV(TY1, TY2)                                            \
  do {                                                                         \
    std::cout << std::boolalpha;                                               \
    out("std::is_same_v(std::remove_cvref_t<", #TY1, ">,",                     \
        "std::remove_cvref_t<", #TY2, ">) ",                                   \
        std::is_same_v<std::remove_cvref_t<TY1>, std::remove_cvref_t<TY2>>);   \
  } while (0);

struct Base {
  virtual ~Base() = default;
};

struct Base2 {
  virtual ~Base2() = default;
};

struct Derived : Base {};

void test_is_same() {
  IS_SAME(int, int);
  IS_SAME(int, const int);
  IS_SAME(int, volatile int);
  IS_SAME(int, char);
  IS_SAME(Base, Derived);
  IS_SAME(Base, Base2);
}

//=============================================================
void test_remove_cvref() {
  IS_SAME_REMOVE_CV(int, int);
  IS_SAME_REMOVE_CV(int, const int);
  IS_SAME_REMOVE_CV(int, volatile int);
  IS_SAME_REMOVE_CV(int, double);

  int a = 42;
  const int &cra = a;
  IS_SAME_REMOVE_CV(decltype(a), decltype(cra));
}

//=============================================================
void test() {
  // todo
  TEST(test_is_same);
  TEST(test_remove_cvref);
}

//=============================================================
int main() { test(); }
