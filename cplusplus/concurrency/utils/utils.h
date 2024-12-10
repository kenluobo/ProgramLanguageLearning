#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <condition_variable>
#include <future>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

using std::mutex;
using std::string;
using std::stringstream;
using std::thread;

template <typename... Args> void out(Args... args) {
  (std::cout << ... << args) << "\n";
}

template <unsigned Time, typename... Args> void out_and_wait(Args... args) {
  unsigned count = Time;
  while (count-- > 0) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    (std::cout << ... << args) << "\n";
  }
}

#endif
