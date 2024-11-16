#include <cstdio>
#include <version>

#define TEST(FUNC)                                                             \
  do {                                                                         \
    std::printf("======[%s]======\n", #FUNC);                                  \
    FUNC();                                                                    \
  } while (0);

#define CONNECT_STRING(...) (#__VA_ARGS__)
