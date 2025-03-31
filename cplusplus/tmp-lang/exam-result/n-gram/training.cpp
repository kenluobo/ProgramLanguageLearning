#include <thread>

#include "n-gram.h"
#include "thread-pool.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: do-training <profile.config> " << std::endl;
  }

  const fs::path configPath(argv[1]);
  ProfileConfig config(configPath);

  // const std::size_t maxThreadNum = std::thread::hardware_concurrency();
  // const std::size_t threadNum = maxThreadNum == 1 ? 1 : maxThreadNum - 1;
  // ThreadPool pool(threadNum);

  for (ProfileConfig::ProfileElement &elem : config.profileElems) {
    // pool.enqueue([&elem]() {
      NGram ngram(elem.trainingFilePath);
      ngram.saveAsFile(elem.outProfilePath);
    // });
  }
}
