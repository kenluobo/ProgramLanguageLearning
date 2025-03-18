#include <chrono>
#include <iostream>
#include <vector>
#include <fmt/format.h>

#include "thread-pool.h"

int main() {
  fmt::print("begin\n");

  ThreadPool pool(4);
  std::vector<std::future<int>> results;

  for (int i = 0; i < 8; ++i) {
    fmt::print("iterator {}\n", i);
    results.emplace_back(pool.enqueue([i] {
      fmt::print("enqueue {}\n", i);
      std::this_thread::sleep_for(std::chrono::seconds(1));
      return i * i;
    }));
  }

  for (auto &&result : results){
    fmt::print("result {}\n", result.get());
  }

  fmt::print("end\n");

  return 0;
}
