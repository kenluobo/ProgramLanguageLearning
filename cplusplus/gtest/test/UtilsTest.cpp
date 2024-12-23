#include "Utils.h"

#include <gtest/gtest.h>

TEST(utils, internal_add) {
  EXPECT_EQ(2, internal_add(1, 1));
  EXPECT_EQ(3.14, internal_add(double{1}, double{2.14}));
  EXPECT_EQ(3, internal_add(1, static_cast<int>(2.14)));
  EXPECT_EQ(std::string("hello world"),
            internal_add(std::string("hello "), std::string("world")));

  EXPECT_NE(3.14, internal_add(1, static_cast<int>(2.14)));
}
