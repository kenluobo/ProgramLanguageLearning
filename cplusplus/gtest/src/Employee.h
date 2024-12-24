#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Person.h"

class Employee : public Person {
public:
  Employee() : Person("A", SexTy::MALE, 10), salary(30000) {}
  Employee(const std::string &name, SexTy sex, short age, double salary)
      : Person(name, sex, age), salary(salary) {}

  [[nodiscard]] std::string getAsString() const override;

  double getSalary() const { return salary; }

private:
  double salary;
};

#endif
