#include "test.h"

#include <optional>

//==============================================================================
std::optional<String> getVectorAsString(const StringVector &StrVec) {
  if (StrVec.empty())
    return std::nullopt;

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

void test_optional() {
  const std::string NullOptStr = "nullopt";

  const StringVector StrVec{"1", "2", "3", "4", "5", "6", "7", "8", "9"};
  const auto Str1 = getVectorAsString(StrVec);
  out(Str1 ? *Str1 : NullOptStr);

  const StringVector StrVec2{};
  const auto Str2 = getVectorAsString(StrVec2);
  out(Str2 ? *Str2 : NullOptStr);
}

//==============================================================================
void test() {
  // todo
  TEST(test_optional);
}

//==============================================================================
int main() { test(); }
