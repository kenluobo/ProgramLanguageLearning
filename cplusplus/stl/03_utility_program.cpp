#include "utils/test.hpp"

#include <csignal>
#include <cstdlib>

//==============================================================
void handle_abort_signal(int signal_no) {
  if (SIGABRT == signal_no) {
    std::cerr << "handle signal: SIGABRT\n";
  } else {
    std::cerr << "handle signal: " << std::to_string(signal_no) << "\n";
  }
  std::_Exit(EXIT_FAILURE);
}

void test_signal_abort() {
  auto previous = std::signal(SIGABRT, handle_abort_signal);
  if (previous == SIG_ERR) {
    std::cerr << "handle signal failure\n";
  } else {
    std::cout << "handle signal success\n";
  }

  std::cout << "finish signal processing\n";
  std::abort();
  std::cout << "unreachable: " << __func__ << "\n";
}

// ==============================================================
void handle_atexit_signal_1() { std::cout << "exit 1\n"; }
void handle_atexit_signal_2() { std::cout << "exit 2\n"; }

void test_signal_exit() {
  const int ret1 = std::atexit(handle_atexit_signal_1);
  const int ret2 = std::atexit(handle_atexit_signal_2);

  if (ret1 or ret2) {
    std::cout << "register handle atexit failure\n";
  }

  std::cout << "return test_signal_exit\n";
}

// ==============================================================
void test() {
  // TEST(test_signal_abort);
  TEST(test_signal_exit);
}

// ==============================================================
int main() { test(); }
