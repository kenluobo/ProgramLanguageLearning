#include "utils/test.hpp"

#include <typeinfo>

//=====================================================
class Base {
public:
  virtual ~Base() { out("call: ", __func__); }
};

class Derived : public Base {
public:
  virtual ~Derived() { out("call: ", __func__); }
};

void test_typeinfo() {
  Base b;
  Derived d;

  Base *ptr;

  ptr = &b;
  out("typeinfo Base: ", typeid(*ptr).name());
  out("typeinfo Base ptr: ", typeid(ptr).name());

  ptr = &d;
  out("typeinfo Derived: ", typeid(*ptr).name());
  out("typeinfo Derived ptr: ", typeid(ptr).name());
}

//=====================================================
class Person {
public:
  Person(int age, std::string name) : age(age), name(name) {}

private:
  int age;
  std::string name;
};

class Employee : public Person {
public:
  Employee(int age, std::string name, double salary)
      : Person(age, name), salary(salary) {}

private:
  double salary;
};

void test_typeinfo_operator_equal() {
  Person p(17, "Tom");
  Employee e(30, "Jony", 100000.66);

  std::string predicate = typeid(p) == typeid(Person) ? "is" : "isn't";
  out("p ", predicate, typeid(Person).name());

  predicate = typeid(e) == typeid(Person) ? "is" : "isn't";
  out("e ", predicate, " Person");

  predicate = typeid(e) == typeid(Employee) ? "is" : "isn't";
  out("e ", predicate, typeid(Employee).name());
}

//=====================================================
void test_typeinfo_cv_type() {
  int a = 42;
  const int ca = 42;
  volatile int va = 42;
  int &ra = a;
  out("typeid int a: ", typeid(a).name());
  out("typeid const int a: ", typeid(ca).name());
  out("typeid volatile int a: ", typeid(va).name());
  out("typeid int reference a: ", typeid(ra).name());

  std::string predicate;

  predicate = typeid(a) == typeid(ca) ? "has" : "has not";
  out("int a ", predicate, " same type with const int ca");

  predicate = typeid(a) == typeid(va) ? "has" : "has not";
  out("int a ", predicate, " same type with volatile int va");

  predicate = typeid(a) == typeid(ra) ? "has" : "has not";
  out("int a ", predicate, " same type with int reference ca");
}

//=====================================================
void test() {
  TEST(test_typeinfo);
  TEST(test_typeinfo_operator_equal);
  TEST(test_typeinfo_cv_type);
}

//=====================================================
int main() { test(); }
