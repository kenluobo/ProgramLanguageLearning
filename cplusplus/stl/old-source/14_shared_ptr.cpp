#include "class_demo.h"
#include "stl.h"

//==============================================================
void test_shared_ptr_1() {
  std::shared_ptr<Base> p_b1(new Base());
  out("p_b1 reference count: ", p_b1.use_count());

  std::shared_ptr<Base> p_b2 = std::make_shared<Base>();
  out("p_b2 reference count: ", p_b2.use_count());

  std::shared_ptr<Base> p_b3(p_b1);
  out("p_b3 reference count: ", p_b3.use_count());
  std::shared_ptr<Base> p_b4 = p_b3;
  out("p_b4 reference count: ", p_b4.use_count());
}

void test_shared_ptr_2() {
  auto p_b1 = std::make_shared<Base>(Base());
  auto p_b2 = p_b1;
  p_b1.reset(); // call ~Base()
  out("p_b1 reference count: ", p_b1.use_count(), "; ",
      "p_b1 address: ", p_b1.get());

  auto p_b3 = std::make_shared<Base>();
  auto p_b4 = std::make_shared<Base>();
  out("before swap: ", "p_b3 address: ", p_b3.get(), "; ",
      "p_b4->address: ", p_b4.get());

  p_b3.swap(p_b4);
  out("after swap: ", "p_b3 address: ", p_b3.get(), "; ",
      "p_b4->address: ", p_b4.get());
}

//==============================================================
void test() {
  TEST(test_shared_ptr_1);
  TEST(test_shared_ptr_2);
}

//==============================================================
int main() { test(); }
