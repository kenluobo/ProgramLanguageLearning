#ifndef STL_H
#define STL_H

#include <csignal>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>
#include <concepts>
#include <initializer_list>
#include <memory>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <version>

#if __cpp_lib_source_location >= 201907L
#include <source_location>
using std::source_location;
#else
#include <experimental/source_location>
using std::experimental::source_location;
#endif

#if __cpp_lib_three_way_comparison >= 201907L
#include <experimental/compare>
#else
#include <compare>
#endif

#endif
