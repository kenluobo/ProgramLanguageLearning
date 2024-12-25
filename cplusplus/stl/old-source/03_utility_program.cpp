#include "stl.h"
#include "test.h"

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
struct Resource {
  ~Resource() { std::cout << "call Resource dtor\n"; }
};

Resource global_resource;

#define recycling_action_before_quick_exit 1
#define no_recycling_action_before_quick_exit 0
template <int N> void handle_quick_exit_signal() {
  if (N == 0) {
    std::cout << N << ": do not execute dtor" << "\n";
  } else {
    global_resource.~Resource();
    std::cout << N << ": do execute dtor" << "\n";
  }
}

void test_quick_exit() {
  int ret1 = at_quick_exit(
      handle_quick_exit_signal<recycling_action_before_quick_exit>);
  int ret2 = at_quick_exit(
      handle_quick_exit_signal<no_recycling_action_before_quick_exit>);
  if (ret1 or ret2) {
    std::cerr << "register handle_quick_exit_signal error\n";
  }

  Resource local_resource;

  std::cout << "before call quick_exit\n";
  std::quick_exit(EXIT_SUCCESS);
  std::cout << "after call quick_exit\n";
}

// ==============================================================
void test_unreachable() {
#ifdef __cpp_lib_unreachable
  std::cout << "before std::unreachable()\n";
  std::unreachable();
  std::cout << "after std::unreachable()\n";
#else

#ifdef __has_builtin

#if __has_builtin(__builtin_unreachable)
  std::cout << "before __builtin_unreachable()\n";
  __builtin_unreachable();
  std::cout << "after __builtin_unreachable()\n";
#endif

#endif

#endif
}

// ==============================================================
void test() {
  // TEST(test_signal_abort);
  // TEST(test_signal_exit);
  // TEST(test_quick_exit);
  TEST(test_unreachable);
}

// ==============================================================
int main() { test(); }
