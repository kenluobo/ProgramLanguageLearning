#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {
public:
  explicit ThreadPool(std::size_t ThreadCount);
  ~ThreadPool();

  void enqueue(std::function<void()> Task);

private:
  void workerLoop();

  std::vector<std::thread> Workers;
  std::queue<std::function<void()>> Tasks;

  std::mutex Mutex;
  std::condition_variable CondVar;
  bool Stop = false;
};

inline ThreadPool::ThreadPool(std::size_t ThreadCount) {
  for (std::size_t I = 0; I < ThreadCount; ++I) {
    Workers.emplace_back([this] { workerLoop(); });
  }
}

inline void ThreadPool::enqueue(std::function<void()> Task) {
  {
    std::unique_lock Lock(Mutex);
    Tasks.push(std::move(Task));
  }
  CondVar.notify_one();
}

inline void ThreadPool::workerLoop() {
  while (true) {
    std::function<void()> Task;
    {
      std::unique_lock Lock(Mutex);
      CondVar.wait(Lock, [this] { return Stop || !Tasks.empty(); });

      if (Stop && Tasks.empty()) {
        return;
      }

      Task = std::move(Tasks.front());
      Tasks.pop();
    }
    Task();
  }
}

inline ThreadPool::~ThreadPool() {
  {
    std::unique_lock Lock(Mutex);
    Stop = true;
  }
  CondVar.notify_all();
  for (std::thread &T : Workers) {
    T.join();
  }
}

#endif // THREAD_POOL_H

