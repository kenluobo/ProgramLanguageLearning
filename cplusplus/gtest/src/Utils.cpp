#include "Utils.h"

std::string getAsString(const std::string &s) {
  std::string Ret;
  Ret.append("{");
  Ret.append(s);
  Ret.append("}");
  return Ret;
}
