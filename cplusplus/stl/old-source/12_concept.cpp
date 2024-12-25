#include "stl.h"
#include "test.h"

// //=====================================================
// template <typename T>
// concept IsDigit = std::integral<T> or std::floating_point<T>;
// void print_number(IsDigit auto const... args) {
//   ((std::cout << ' ' << args), ...) << '\n';
// }
//
// void test_same_as() { print_number(1, 2, 3, 4.5, 6.7); }
//
// //=====================================================
// class Base {};
// class Derived : public Base {};
//
// template <typename BaseTy, typename DerivedTy>
// void print_base_and_derived_class(const BaseTy &b, const DerivedTy &t) {
//   if (not std::derived_from<DerivedTy, BaseTy>) {
//     out(typeid(DerivedTy).name(), " is not derived from ",
//         typeid(BaseTy).name());
//   }else{
//     out("Derived Class: ", typeid(DerivedTy).name(),"; Base Class: ",
//         typeid(BaseTy).name());
//   }
// }
//
// void test_derived_from() {
//   const Base b;
//   volatile Derived d;
//
//   std::cout << std::boolalpha;
//   out(std::derived_from<decltype(d), decltype(b)> == true);
//
//
//   print_base_and_derived_class(b,d);
//   print_base_and_derived_class(d,b);
// }
//
// //=====================================================
// void test() {
//   TEST(test_same_as);
//   TEST(test_derived_from);
// }
//
// //=====================================================
// int main() { test(); }

int main() {}