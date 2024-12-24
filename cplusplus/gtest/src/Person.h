#ifndef PERSON_H
#define PERSON_H

#include "Utils.h"

enum class SexTy { MALE, FEMALE };

extern std::string getSexAsString(SexTy s);

class Person {
public:
  Person() = default;
  Person(const std::string &name, SexTy sex, short age)
      : name(name), sex(sex), age(age) {}

  virtual std::string getAsString() const;

  std::string getName() const { return name; }

  SexTy getSex() const { return sex; }

  short getAge() const { return age; }

protected:
  std::string name;
  SexTy sex;
  short age;
};

#endif
