#include <cstdio>
#include <iostream>
#include <version>

#define TEST(FUNC, ...)                                                        \
  do {                                                                         \
    std::printf("======[%s]======\n", #FUNC);                                  \
    FUNC(__VA_ARGS__);                                                         \
  } while (0);

#define CONNECT_STRING(...) (#__VA_ARGS__)

template <typename... Args> void out(Args... args) {
  (std::cout << ... << args) << "\n";
}

#define OUT_FUNC_INFO(...)                                                     \
  do {                                                                         \
    out("Current Func: ", __PRETTY_FUNCTION__, " ",                            \
        CONNECT_STRING(__VA_ARGS__));                                          \
  } while (0);
