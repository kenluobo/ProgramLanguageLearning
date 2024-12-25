#ifndef CONTAINER_TO_STRING_H
#define CONTAINER_TO_STRING_H

#include "stl.h"

static String getStringVectorAsString(const StringVector &StrVec) {
  if (StrVec.empty())
    return "[]";

  StringStream SS;
  const unsigned Len = StrVec.size();
  unsigned Count = 0U;

  SS << "[";
  std::for_each(StrVec.begin(), StrVec.end(), [&](const String &Str) {
    SS << Str << (++Count < Len ? ", " : "");
  });
  SS << "]";

  return SS.str();
}

#endif
