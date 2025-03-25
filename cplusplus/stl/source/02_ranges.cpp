#include "common.h"
#include <algorithm>
#include <functional>
#include <gtest/gtest.h>
#include <iterator>
#include <sstream>
#include <vector>

TEST(Ranges, outIterator) {
  std::ostream_iterator<int> outIter(std::cout, " "); 
  std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9};
  // std::ranges::copy(nums, outIter);
  // std::cout << std::endl;
}

TEST(Ranges, copyVector) {
  std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> nums2;
  std::ranges::copy(nums, std::back_inserter(nums2));
  EXPECT_EQ(nums, nums2);
}

TEST(Ranges, foreach) {
  std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::ostringstream oss;
  std::ranges::for_each(nums, [&oss](int num) { oss << num << " "; });
  EXPECT_EQ(oss.str(), "1 2 3 4 5 6 7 8 9 ");
}

TEST(Ranges, fill) {
  std::vector<int> nums(10);
  std::ranges::fill(nums, 1);
  EXPECT_EQ(nums, std::vector<int>(10, 1));
}

TEST(Ranges, fill_n){
  std::vector<int> nums(10);
  std::ranges::fill_n(nums.begin(), 5, 1);
  EXPECT_NE(nums, std::vector<int>(10, 1));
}

TEST(Ranges, generate_n){
  std::vector<int> lhs{1, 2, 3, 4, 5, 6, 7, 8, 9};
  
  std::vector<int> rhs;
  std::ranges::generate_n(std::back_inserter(rhs), lhs.size(), [n = 0]() mutable { return ++n; });

  EXPECT_EQ(lhs, rhs);
}

TEST(Ranges, equal){
  std::vector<int> lhs{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> rhs{1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_TRUE(std::ranges::equal(lhs, rhs));
}

TEST(Ranges, mismatch){
  std::vector<int> lhs{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> rhs{1, 2, 3, 4, 5, 6, 7, 8, 10};
  auto [lhs_iter, rhs_iter] = std::ranges::mismatch(lhs, rhs);
  // auto location {std::ranges::mismatch(lhs, rhs)};
  EXPECT_EQ(*lhs_iter, 9);
  EXPECT_EQ(*rhs_iter, 10);
}

TEST(Ranges, remove){
  std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto removed = std::ranges::remove(nums, 5);
  nums.erase(removed.begin(), removed.end());
  EXPECT_TRUE(std::ranges::equal(nums, std::vector<int>{1, 2, 3, 4, 6, 7, 8, 9}));
}

TEST(Ranges, remove_copy){
  std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> nums2;
  std::ranges::remove_copy(nums, std::back_inserter(nums2), 5);
  EXPECT_TRUE(std::ranges::equal(nums2, std::vector<int>{1, 2, 3, 4, 6, 7, 8, 9}));
}

TEST(Ranges, remove_if){
  std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto removed = std::ranges::remove_if(nums, [](int num) { return num % 2 == 0; });

  // std::ranges::for_each(nums, [](int num) { std::cout << num << " "; }); 
  // std::cout << std::endl;

  EXPECT_TRUE(std::ranges::equal(nums, std::vector<int>{1, 3, 5, 7, 9, 6, 7, 8, 9}));

  EXPECT_TRUE(std::ranges::equal(removed, std::vector<int>{6, 7, 8, 9}));
}

TEST(Ranges, sort){
  std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9};
  // std::ranges::sort(nums, std::greater_equal<>{});
  std::ranges::sort(nums, std::ranges::greater_equal{});
  EXPECT_TRUE(std::ranges::equal(nums, std::vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1}));
}

TEST(Ranges, sort_projection){
  std::vector<Person> persons{Person{"John", 20, 1000.0f}, Person{"Jane", 30, 2000.0f}, Person{"Jack", 40, 3000.0f}};

  std::ranges::sort(persons, std::ranges::less_equal{}, &Person::getName);

  std::vector<Person> expectedPersons{
      Person{"Jack", 40, 3000.0f}, 
      Person{"Jane", 30, 2000.0f}, 
      Person{"John", 20, 1000.0f}
  };
  
  EXPECT_TRUE(std::ranges::equal(persons, expectedPersons, 
    [](const Person& lhs, const Person& rhs)->bool {
      return lhs.getName() == rhs.getName() 
      && lhs.getAge() == rhs.getAge() 
      && lhs.getSalary() == rhs.getSalary();
    }));
}
