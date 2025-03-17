#include <cmath>
#include <fmt/format.h>
#include <future>
#include <iostream>
#include <thread>

int calculateSum(int a, int b) { return a + b; }

int main() {
  std::packaged_task<int()> task([] { return calculateSum(40, 2); });
  std::future<int> ret = task.get_future();

  std::thread t(std::move(task));
  t.join();

  fmt::print("Result is {}\n", ret.get());
}
