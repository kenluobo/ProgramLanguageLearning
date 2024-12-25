#include "test.h"

//==============================================================================
struct Country {
  std::string name;
  std::string area;
  unsigned age;
  unsigned population;

  Country() : name("none"), area("none"), age(0), population(0) {
    OUT_FUNC_INFO();
  }

  void operator()() const { out(get_as_string()); }

  void out_hello(int time) const {
    while (time-- > 0) {
      out("country hello; " + get_as_string());
    }
  }

  void out_country_hello(int time) const {
    while (time-- > 0) {
      out("country hello; " + get_as_string());
    }
  }

  void out_country_hello(int time, unsigned no) const {
    while (time-- > 0) {
      out("[", no, "]\t", "country hello; " + get_as_string());
    }
  }

  [[nodiscard]] std::string get_as_string() const {
    std::stringstream ss;
    ss << "{name: " << name << "}, ";
    ss << "{area: " << area << "}, ";
    ss << "{age: " << age << "}, ";
    ss << "{population: " << population << "}";
    return ss.str();
  }
};

void test_function_object1() {
  Country country;
  out("typeid(country): ", typeid(country).name());

  auto obj = Country();
  out("typeid(func): ", typeid(obj).name());
  obj();

  const std::function<void()> func1 = Country();
  func1();
}
//==============================================================================
void test_function_object2() {
  const std::function<void(const Country &, int)> func = &Country::out_hello;
  func(Country(), 3);
}

//==============================================================================
void test_function_object_bind() {
  Country country;

  std::function<void(int)> func =
      std::bind(&Country::out_hello, &country, std::placeholders::_1);
  func(2);

  // error:
  // std::function<void(int, unsigned)> func =
  //     std::bind(&Country::out_country_hello, country, std::placeholders::_1,
  //               std::placeholders::_2);
}

//==============================================================================
void test() {
  TEST(test_function_object1);
  TEST(test_function_object2);
  TEST(test_function_object_bind);
}

//==============================================================================
int main() { test(); }
