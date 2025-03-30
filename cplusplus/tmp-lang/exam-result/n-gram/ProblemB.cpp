#include <algorithm>
#include <cctype>
#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// 将非字母和数字字符替换为'_'
char replaceNonAlphaNum(char c) { return (isspace(c) || isdigit(c)) ? '_' : c; }

// 提取n-gram
void extractNGrams(const string &text, int n, map<string, int> &ngramMap) {
  string cleanedText;
  // 清理文本，替换空白字符和数字
  for (char c : text) {
    cleanedText.push_back(replaceNonAlphaNum(c));
  }

  // 提取n-grams
  for (int i = 0; i <= cleanedText.size() - n; ++i) {
    string ngram = cleanedText.substr(i, n);
    ngramMap[ngram]++;
  }
}

// 计算“out-of-place”距离
int calculateOutOfPlaceDistance(const map<string, int> &docProfile,
                                const map<string, int> &catProfile) {
  int distance = 0;
  // 遍历文档的n-grams
  for (const auto &docNgram : docProfile) {
    auto it = catProfile.find(docNgram.first);
    if (it != catProfile.end()) {
      // 找到相应n-gram的频率，计算其顺序差
      int rankDoc = distance; // 排序位置
      int rankCat = distance;
      distance += abs(rankDoc - rankCat);
    } else {
      // 如果该n-gram在类别档案中不存在，使用最大距离值
      distance += 400;
    }
  }
  return distance;
}

// 识别文本的语言
void identifyLanguage(const string &configFile, const string &inputFile,
                      const string &outputFile) {
  ifstream config(configFile);
  vector<pair<string, map<string, int>>> languageProfiles;
  string line;

  // 读取语言档案
  while (getline(config, line)) {
    stringstream ss(line);
    string trainFile, profileFile, language;
    ss >> trainFile >> profileFile >> language;

    ifstream profile(profileFile);
    map<string, int> ngramProfile;
    string ngram;
    int count;
    while (profile >> ngram >> count) {
      ngramProfile[ngram] = count;
    }
    languageProfiles.push_back({language, ngramProfile});
  }

  ifstream input(inputFile);
  ofstream output(outputFile);
  string text;

  // 对每一行文本进行语言识别
  while (getline(input, text)) {
    map<string, int> docProfile;
    for (int n = 1; n <= 5; ++n) {
      extractNGrams(text, n, docProfile);
    }

    // 计算与每种语言档案的距离
    string identifiedLanguage;
    int minDistance = INT_MAX;
    for (const auto &langProfile : languageProfiles) {
      int distance =
          calculateOutOfPlaceDistance(docProfile, langProfile.second);
      if (distance < minDistance) {
        minDistance = distance;
        identifiedLanguage = langProfile.first;
      }
    }
    output << identifiedLanguage << endl;
  }
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    cerr << "Usage: ProblemA2 profile.config input_file output_file" << endl;
    return 1;
  }

  string configFile = argv[1];
  string inputFile = argv[2];
  string outputFile = argv[3];

  identifyLanguage(configFile, inputFile, outputFile);

  return 0;
}
