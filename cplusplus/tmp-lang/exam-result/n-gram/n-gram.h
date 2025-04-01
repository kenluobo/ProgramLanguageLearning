#ifndef N_GRAM_H
#define N_GRAM_H

#include <tsl/robin_map.h>

#include <algorithm>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

struct ProfileConfig {
  explicit ProfileConfig(const fs::path& profilePath) {
    if (!fs::exists(profilePath)) {
      std::cerr << std::format("Error: profile path does not exist: {}\n",
                               profilePath.string());
    }

    std::ifstream ifs(profilePath);
    if (!ifs.is_open()) {
      std::cerr << std::format("Error: failed to open file: {}\n",
                               profilePath.string());
    }

    std::string line;
    while (std::getline(ifs, line)) {
      profileElems.emplace_back(line);
    }
  }

  struct ProfileElement {
    explicit ProfileElement(const std::string& text) {
      std::istringstream iss(text);
      iss >> trainingFilePath >> outProfilePath >> language;
    }

    fs::path trainingFilePath;
    fs::path outProfilePath;
    std::string language;
  };

  std::vector<ProfileElement> profileElems;
};

class NGram {
 public:
  explicit NGram(const fs::path& inputFile,
                 const std::size_t maxReversedLine = 400) {
    std::ifstream ifs(inputFile);
    if (!ifs.is_open()) {
      std::cerr << std::format("Error: failed to open file: {}\n",
                               inputFile.string());
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
      std::cerr << std::format("Warn: the file is empty: {}\n",
                               inputFile.string());
      return;
    }

    std::string normalizedText = normalize(text);
    if (normalizedText.empty()) {
      std::cerr << std::format("Warn: the file is empty: {}\n",
                               inputFile.string());
      return;
    }
    std::cout << normalizedText << std::endl;

    Word2FrequencyTy w2f;
    w2f.reserve((1 + normalizedText.size()) * normalizedText.size() / 2);
    std::uint64_t calculateTimes = normalizedText.size();
    do {
      staticticalWordFrequency(normalizedText, calculateTimes--, w2f);
    } while (calculateTimes > 0);

    Word2FrequencyVectorTy vec;
    calculateNGram(w2f, vec, maxReversedLine);

    word2FrequencyResult = std::move(vec);
  }

  void saveAsFile(const fs::path& outputFile) {
    fs::path parentDir = outputFile.parent_path();
    if (!fs::exists(parentDir) && !fs::create_directory(parentDir)) {
      std::cerr << std::format("Error: failed to create directory: {}\n",
                               parentDir.string());
    }

    std::ofstream ofs(outputFile);
    if (!ofs.is_open()) {
      std::cerr << std::format("Error: failed to open file: {}\n",
                               outputFile.string());
      return;
    }

    std::for_each(word2FrequencyResult.begin(), word2FrequencyResult.end(),
                  [&ofs](const auto& w2f) {
                    ofs << w2f.second << " " << w2f.first << "\n";
                  });

    ofs.close();
  }

 private:
  using Word2FrequencyTy = tsl::robin_map<std::string_view, unsigned>;
  using Word2FrequencyVectorTy =
      std::vector<std::pair<std::string_view, unsigned>>;

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

  void staticticalWordFrequency(const std::string& normalizedText,
                                std::size_t windowSize, Word2FrequencyTy& w2f) {
    auto left = normalizedText.begin();
    auto right = std::next(left, windowSize);
    auto end = normalizedText.end();
    while (left != end && right != end) {
      const std::string_view currStr(
          normalizedText.data() + std::distance(normalizedText.begin(), left),
          windowSize);
      if (auto it = w2f.find(currStr); it != w2f.end()) {
        ++w2f[currStr];
      } else {
        w2f.emplace(currStr, 1);
      }

      std::cout << std::format(
                       "w2f size: {}/{}", w2f.size(),
                       (1 + normalizedText.size()) * normalizedText.size() / 2)
                << std::endl;

      left = std::next(left, 1);
      right = std::next(right, 1);
    }
  }

  void calculateNGram(const Word2FrequencyTy w2f, Word2FrequencyVectorTy& vec,
                      std::size_t maxReversedLine) {
    vec.assign(w2f.begin(), w2f.end());
    auto comOp = [](const auto& a, const auto& b) {
      if (a.second != b.second) return a.second > b.second;
      return a.first < b.first;
    };

    if (vec.size() > maxReversedLine) {
      std::partial_sort(vec.begin(), std::next(vec.begin(), maxReversedLine),
                        vec.end(), comOp);
      vec.resize(maxReversedLine);
    } else {
      std::sort(vec.begin(), vec.end(), comOp);
    }
  }

 private:
  Word2FrequencyVectorTy word2FrequencyResult;
};

#endif
