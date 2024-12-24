#include "Utils.h"

template <> int internalAdd(int a, int b) { return a + b; }

template <> std::string internalAdd(std::string a, std::string b) {
  return a + b;
}

std::string getAsString(const std::string &s) {
  std::string Ret;
  Ret.append("{");
  Ret.append(s);
  Ret.append("}");
  return Ret;
}
