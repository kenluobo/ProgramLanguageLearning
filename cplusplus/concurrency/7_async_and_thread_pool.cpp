#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {
public:
  explicit ThreadPool(size_t numThreads) {
    for (size_t i = 0; i < numThreads; ++i) {
      workers.emplace_back([this] {
        while (true) {
          std::function<void()> task;
          {
            std::unique_lock<std::mutex> lock(queue_mutex);
            condition.wait(lock, [this] { return !tasks.empty() || stop; });

            if (stop && tasks.empty())
              return;

            task = std::move(tasks.front());
            tasks.pop();
          }
          task(); // 执行任务
        }
      });
    }
  }

  ~ThreadPool() {
    {
      std::lock_guard<std::mutex> lock(queue_mutex);
      stop = true;
    }
    condition.notify_all();
    for (std::thread &worker : workers)
      worker.join();
  }

  template <typename Func, typename... Args>
  auto submit(Func &&func, Args &&...args)
      -> std::future<typename std::invoke_result<Func, Args...>::type> {
    using ReturnType = typename std::invoke_result<Func, Args...>::type;

    auto task = std::make_shared<std::packaged_task<ReturnType()>>(
        std::bind(std::forward<Func>(func), std::forward<Args>(args)...));

    std::future<ReturnType> result = task->get_future();

    {
      std::lock_guard<std::mutex> lock(queue_mutex);
      tasks.emplace([task]() { (*task)(); });
    }
    condition.notify_one();

    return result;
  }

private:
  std::vector<std::thread> workers;
  std::queue<std::function<void()>> tasks;
  std::mutex queue_mutex;
  std::condition_variable condition;
  bool stop = false;
};

int ComputeSum(int a, int b) { return a + b; }

int main() {
  ThreadPool pool(4);

  auto future1 = pool.submit(ComputeSum, 10, 20);
  auto future2 = pool.submit([] { return 42; });

  std::cout << "Result1: " << future1.get() << std::endl;
  std::cout << "Result2: " << future2.get() << std::endl;

  return 0;
}

