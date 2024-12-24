#include "Person.h"
#include <fmt/core.h>

std::string getSexAsString(SexTy s) {
  switch (s) {
  case SexTy::MALE:
    return "Male";
  case SexTy::FEMALE:
  default:
    return "Female";
  }
}

std::string Person::getAsString() const {
  return fmt::format(
      "{{name: {name}, sex: {sex}, age: {age}}}", fmt::arg("name", name),
      fmt::arg("sex", getSexAsString(sex)), fmt::arg("age", age));
}
