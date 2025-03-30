#ifndef N_GRAM_H
#define N_GRAM_H

#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <vector>

class NGram {
 public:
  explicit NGram(const std::string& inputFile,
                 const std::size_t maxWindowSize = 400) {
    std::ifstream ifs(inputFile);
    if (!ifs.is_open()) {
      std::cerr << std::format("Error: failed to open file: {}\n", inputFile);
      return;
    }

    std::string text;
    std::string line;
    while (std::getline(ifs, line)) {
      text.append(line);
      text.append(" ");  // add '\n' to the end of line
    }

    if (!text.empty()) {
      text.pop_back();  // remove last character '\n'
    } else {
      std::cerr << std::format("Warn: the file is empty: {}\n", inputFile);
      return;
    }

    std::string normalizedText = normalize(text);
    std::cout << std::format("{}\n", normalizedText);
    Frequency2WordTy f2w;
    calculateNGram(f2w, normalizedText, maxWindowSize);
  }

  void saveAsFile(const std::string& outputFile);

 private:
  using Frequency2WordTy = std::multimap<unsigned, std::string, std::less<>>;

 private:
  std::string normalize(const std::string& text) {
    std::string normalizedText;

    auto isSpaceOrDigit = [](char ch) { return isdigit(ch) || isspace(ch); };

    bool beforeCharacterIsSpaceOrDigit = false;  // character is space or digit
    for (char ch : text) {
      if (isSpaceOrDigit(ch)) {
        beforeCharacterIsSpaceOrDigit = true;
      } else {
        if (beforeCharacterIsSpaceOrDigit) {
          normalizedText.push_back('_');
          beforeCharacterIsSpaceOrDigit = false;
        }
        normalizedText.push_back(ch);
      }
    }

    return normalizedText;
  }

  void calculateNGram(Frequency2WordTy &f2w, const std::string& normalizedText,
                      std::size_t windowSize) {
    // todo
  }
};

#endif
