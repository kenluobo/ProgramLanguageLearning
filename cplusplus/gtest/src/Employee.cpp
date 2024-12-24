#include "Employee.h"
#include <fmt/core.h>

std::string Employee::getAsString() const {
  return fmt::format("{name: {name}, sex: {sex}, age: {age}, salary: {salary}",
                     fmt::arg("name", name),
                     fmt::arg("sex", getSexAsString(sex)), fmt::arg("age", age),
                     fmt::arg("salary", salary));
}
