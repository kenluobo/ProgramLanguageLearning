#include "Utils.h"

template <> int internal_add(int a, int b) { return a + b; }

template <> std::string internal_add(std::string a, std::string b) {
  return a + b;
}

std::string get_as_string(const std::string &s) {
  std::string Ret;
  Ret.append("{");
  Ret.append(s);
  Ret.append("}");
  return Ret;
}
