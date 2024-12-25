#ifndef STL_H
#define STL_H

#include <csignal>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>
#include <any>
#include <functional>
#include <initializer_list>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <variant>
#include <version>

#if defined(__cpp_lib_source_location) && __cpp_lib_source_location >= 201907L
#include <source_location>
using std::source_location;
#else
#include <experimental/source_location>
using std::experimental::source_location;
#endif

#if defined(__cpp_lib_three_way_comparison) &&                                 \
    __cpp_lib_three_way_comparison >= 201907L
#include <compare>
#endif

using String = std::string;
using StringStream = std::stringstream;

using StringVector = std::vector<String>;
using StringSet = std::set<String>;
using StringMap = std::map<String, String>;

#endif
