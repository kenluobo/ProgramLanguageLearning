#include "common.h"

TEST(Algorithm, accumulate) {
  std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9};
  int sum = std::accumulate(nums.cbegin(), nums.cend(), 0);
  EXPECT_EQ(sum, (1 + 9) * nums.size() / 2 /*calculate nums sum*/);
}
