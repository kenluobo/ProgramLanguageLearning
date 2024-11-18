#include <cstdio>
#include <iostream>
#include <version>

#define TEST(FUNC, ...)                                                        \
  do {                                                                         \
    std::printf("======[%s]======\n", #FUNC);                                  \
    FUNC(__VA_ARGS__);                                                         \
  } while (0);

#define CONNECT_STRING(...) (#__VA_ARGS__)
