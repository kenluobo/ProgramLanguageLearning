#ifndef UTILS_H
#define UTILS_H

#include <string>

template<typename T>
T internal_add(T a, T b) {
    return a + b;
}

std::string getAsString(const std::string& s);

#endif
