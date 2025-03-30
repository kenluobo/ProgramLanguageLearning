#include "n-gram.h"

int main(int argc, char *argv[]) {
  std::vector<std::string> files;
  char *currArg;
  std::size_t pos = 1;
  while ((currArg = argv[pos++]) != nullptr) {
    files.emplace_back(currArg);
  }

  for (const auto &currFile : files) {
    NGram ngram(currFile);
    ngram.saveAsFile("test-out.txt");
  }
}
