#ifndef N_GRAM_H
#define N_GRAM_H

#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <algorithm>
#include <numeric>

class NGram {
public:
  explicit NGram(const std::string &inputFile,
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
      text.append(" "); // add '\n' to the end of line
    }

    if (!text.empty()) {
      text.pop_back(); // remove last character '\n'
    } else {
      std::cerr << std::format("Warn: the file is empty: {}\n", inputFile);
      return;
    }

    std::string normalizedText = normalize(text);

    Word3FrequencyTy w2f;
    std::uint64_t calculateTimes =
        std::min(normalizedText.size(), maxWindowSize);
    do {
      staticticalWordFrequency(normalizedText, calculateTimes--, w2f);
    } while (calculateTimes > 0);

    Frequency2WordTy f2w;
    calculateNGram(w2f, f2w);

    frequency2Word = std::move(f2w);
  }

  void saveAsFile(const std::string &outputFile) {
    std::ofstream ofs(outputFile);
    if (!ofs.is_open()) {
      std::cerr << std::format("Error: failed to open file: {}\n", outputFile);
      return;
    }

    std::ranges::for_each(this->frequency2Word, [&ofs](const auto &w2f) {
      ofs << w2f.second << " " << w2f.first << "\n";
    });

    ofs.close();
  }

private:
  using Word3FrequencyTy = std::map<std::string, unsigned, std::less<>>;
  using Frequency2WordTy = std::multimap<unsigned, std::string, std::greater<>>;

private:
  std::string normalize(const std::string &text) {
    std::string normalizedText;

    auto isSpaceOrDigit = [](char ch) { return isdigit(ch) || isspace(ch); };

    bool beforeCharacterIsSpaceOrDigit = false; // character is space or digit
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

  void staticticalWordFrequency(const std::string &normalizedText,
                                std::size_t windowSize, Word3FrequencyTy &f2w) {
    auto left = normalizedText.begin();
    auto right = std::next(left, windowSize);
    auto end = normalizedText.end();
    while (left != end && right != end) {
      const std::string_view currStr(left, right);
      if (auto it = f2w.find(currStr); it != f2w.end()) {
        it->second++;
      }else {
        f2w.emplace(currStr, 1);
      }

      left = std::next(left, 1);
      right = std::next(right, 1);
    }
  }

  void calculateNGram(const Word3FrequencyTy w2f, Frequency2WordTy &f2w) {
    for (const auto &[word, frequency] : w2f) {
      f2w.emplace(frequency, word);
    }
  }

private:
  Frequency2WordTy frequency2Word;
};

#endif
