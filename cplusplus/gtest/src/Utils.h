#ifndef UTILS_H
#define UTILS_H

#include <string>

///=============================================================================
template <typename T> T internalAdd(T a, T b) { return a + b; }

template <> int internalAdd(int a, int b);

template <> std::string internalAdd(std::string a, std::string b);

///=============================================================================
std::string getAsString(const std::string &s);

#endif
