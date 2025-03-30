#include <algorithm>
#include <cctype>
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
void extractNGrams(const string& text, int n, map<string, int>& ngramMap) {
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

// 生成语言的n-gram频率档案
void generateNGramProfile(const string& inputFile, const string& outputFile) {
  ifstream infile(inputFile);
  stringstream buffer;
  buffer << infile.rdbuf();
  string text = buffer.str();

  map<string, int> ngramFrequency;

  // 提取1-gram到5-gram
  for (int n = 1; n <= 5; ++n) {
    extractNGrams(text, n, ngramFrequency);
  }

  // 将n-grams按频率降序排列
  vector<pair<string, int>> ngramVector(ngramFrequency.begin(),
                                        ngramFrequency.end());
  sort(ngramVector.begin(), ngramVector.end(),
       [](const pair<string, int>& a, const pair<string, int>& b) {
         if (a.second == b.second) return a.first < b.first;  // 字典序排列
         return a.second > b.second;                          // 按频率降序排列
       });

  // 输出前400个n-grams
  ofstream outfile(outputFile);
  int count = 0;
  for (const auto& ngram : ngramVector) {
    if (count >= 400) break;
    outfile << ngram.first << " " << ngram.second << endl;
    count++;
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Usage: ProblemA1 profile.config" << endl;
    return 1;
  }

  string configFile = argv[1];
  ifstream config(configFile);
  string line;

  // 读取配置文件，逐行处理
  while (getline(config, line)) {
    stringstream ss(line);
    string trainFile, profileFile, language;
    ss >> trainFile >> profileFile >> language;
    generateNGramProfile(trainFile, profileFile);
  }

  return 0;
}
