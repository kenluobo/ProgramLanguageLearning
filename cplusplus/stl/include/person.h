#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <format>

class Person{

  public:
    Person(std::string name, int age = 0, float salary = 0.0f) : name{name}, age{age}, salary{salary} {}

    std::string getName() const { return name; }

    int getAge() const { return age; }

    float getSalary() const { return salary; }

    std::string getAsString() const {
      return std::format("Name: {}, Age: {}, Salary: {}", name, age, salary);
    }

  private:
    std::string name;
    int age;
    float salary;
};

#endif
