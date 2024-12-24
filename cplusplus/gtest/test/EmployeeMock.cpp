#include "Employee.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

class EmployeeMock : public Employee {
public:
  MOCK_METHOD0(getAsString, std::string(void));
};

using ::testing::Return;
TEST(Employee, getAsString) {
  EmployeeMock EM;
  EXPECT_CALL(EM, getAsString()).Times(1).WillOnce(Return("XXX"));
  // EXPECT_CALL(EM, getAsString());
  EXPECT_EQ(EM.getAsString(), "XXX")
      << "getAsString(): " << EM.getAsString() << std::endl;

  // default ctor set name = "A", sex = MALE, age = 10, salary = 30000
  EXPECT_EQ(EM.getName(), "A") << "getName(): " << EM.getName() << std::endl;
  EXPECT_EQ(EM.getAge(), 10) << "getAge(): " << EM.getAge() << std::endl;
  EXPECT_EQ(EM.getSex(), SexTy::MALE)
      << "getSex(): " << getSexAsString(EM.getSex()) << std::endl;
  EXPECT_EQ(EM.getSalary(), 30000)
      << "getSalary(): " << EM.getSalary() << std::endl;
}
