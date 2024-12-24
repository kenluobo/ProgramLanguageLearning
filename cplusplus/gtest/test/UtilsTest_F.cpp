#include "Person.h"
#include "Utils.h"
#include <gtest/gtest.h>

class PersonEmployee : public ::testing::Test {
protected:
  void SetUp() override {
    student = Person("student1", SexTy::MALE, 12);
    cooker = Person("cooker1", SexTy::FEMALE, 26);
  }

  void TearDown() override {}

  Person student;
  Person cooker;
};

TEST_F(PersonEmployee, getAsString) {
  EXPECT_NE("student1", student.getAsString());
  EXPECT_EQ("cooker1", cooker.getName());
}
