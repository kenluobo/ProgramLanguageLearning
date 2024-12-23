#ifndef UTILS_H
#define UTILS_H

#include <string>

///=============================================================================
template <typename T> T internal_add(T a, T b) { return a + b; }

template <> int internal_add(int a, int b);

template <> std::string internal_add(std::string a, std::string b);

///=============================================================================
std::string get_as_string(const std::string &s);

#endif
