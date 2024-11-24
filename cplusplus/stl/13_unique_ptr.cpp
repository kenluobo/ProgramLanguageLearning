#include "class_demo.h"
#include "stl.h"
#include "test.h"

//====================================================
void test_unique_ptr_1() {
  std::unique_ptr<Base> p_b1(new Base());
  std::unique_ptr<Base> p_b2 = std::make_unique<Base>();
  std::unique_ptr<Base> p_b3 = std::move(p_b2);
  std::unique_ptr<Base> p_b4 = std::make_unique<Base>(*p_b3);
}

void test_unique_ptr_2() {
  std::unique_ptr<Base> p_b1 = std::make_unique<Derived>();
  p_b1->out_msg();                            // Derived::otu_msg
  p_b1.get()->out_msg();                      // Derived::out_msg
  static_cast<Base *>(p_b1.get())->out_msg(); // Derived::out_msg

  p_b1->Base::out_msg(); // Base::out_msg
}

//====================================================
void test() {
  TEST(test_unique_ptr_1);
  TEST(test_unique_ptr_2);
}

//====================================================
int main() { test(); }
