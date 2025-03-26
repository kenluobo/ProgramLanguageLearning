#include "common.h"
#include <iterator>

TEST(Views, filter) {
  auto v = std::views::iota(0, 10);
  auto ret = v | std::views::filter([](int i) { return i % 2 != 0; });

  EXPECT_TRUE(std::ranges::equal(ret, std::vector<int>{1, 3, 5, 7, 9}));
}

TEST(Views, transform) {
  auto square = [](int i) { return i * i; };
  auto v = std::views::iota(0, 10);
  auto ret = v | std::views::transform(square);
  EXPECT_TRUE(std::ranges::equal(ret, std::vector<int>{0, 1, 4, 9, 16, 25, 36, 49, 64, 81}));
}

TEST(Views, take) {
  auto data = std::views::iota(0, 10);
  auto ret = data | std::views::take(5);
  EXPECT_TRUE(std::ranges::equal(ret, std::views::iota(0, 5)));
}

TEST(Views, drop){
  auto data = std::views::iota(0, 10);
  auto ret = data | std::views::drop(5);
  EXPECT_TRUE(std::ranges::equal(ret, std::views::iota(5, 10)));
}

TEST(Views, take_while) {
  auto data = std::views::iota(0, 10);
  auto ret = data | std::views::take_while([](int i) { return i % 2 == 0; });

  EXPECT_TRUE(std::ranges::equal(ret, std::views::iota(0, 1)));
}

TEST(Views, drop_while) {
  auto data = std::views::iota(0, 10);
  auto ret = data | std::views::drop_while([](int i) { return i % 2 == 0; });

  EXPECT_TRUE(std::ranges::equal(ret, std::views::iota(1, 10)));
}
