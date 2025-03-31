#ifndef N_GRAM_H
#define N_GRAM_H

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
    if(normalizedText.empty()) {
      std::cerr << std::format("Warn: the file is empty: {}\n",
                               inputFile.string());
      return;
    }
    std::cout << normalizedText << std::endl;

    Word3FrequencyTy w2f;
    std::uint64_t calculateTimes = normalizedText.size();
    do {
      staticticalWordFrequency(normalizedText, calculateTimes--, w2f);
    } while (calculateTimes > 0);

    Frequency2WordTy f2w;
    calculateNGram(w2f, f2w, maxReversedLine);

    frequency2Word = std::move(f2w);
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

    std::for_each(frequency2Word.begin(), frequency2Word.end(),
                  [&ofs](const auto& w2f) {
                    ofs << w2f.second << " " << w2f.first << "\n";
                  });

    ofs.close();
  }

 private:
  using Word3FrequencyTy = std::pmr::unordered_map<std::string_view, unsigned, std::less<>>;
  using Frequency2WordTy = std::multimap<unsigned, std::string_view, std::greater<>>;

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
                                std::size_t windowSize, Word3FrequencyTy& f2w) {
    auto left = normalizedText.begin();
    auto right = std::next(left, windowSize);
    auto end = normalizedText.end();
    while (left != end && right != end) {
      const std::string_view currStr(left, right);
      if (auto it = f2w.find(currStr); it != f2w.end()) {
        it->second++;
      } else {
        f2w.emplace(currStr, 1);
      }

      left = std::next(left, 1);
      right = std::next(right, 1);
    }
  }

  void calculateNGram(const Word3FrequencyTy w2f, Frequency2WordTy& f2w, std::size_t maxReversedLine) {
    unsigned count = 1;
    for (const auto& [word, frequency] : w2f) {
      if(count++ > maxReversedLine) {
        break;
      }

      f2w.emplace(frequency, word);
    }
  }

 private:
  Frequency2WordTy frequency2Word;
};

#endif
