#include "utils.h"

std::mutex mtx;
std::condition_variable t_cond;
bool start_flag = false;

void out_some_time(const string &msg, int count) {
  while (count-- > 0) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    out(msg);
  }
}

//==============================================================================
void first_func() {
  std::lock_guard<mutex> lck(mtx);
  out_some_time(__func__, 3);
  start_flag = true;
  t_cond.notify_one();
}

void second_func() {
  std::unique_lock<mutex> u_lck(mtx);
  t_cond.wait(u_lck, [&] { return start_flag; });
  out_some_time(__func__, 1);
}

void test_thread_condition_variable() {
  out_some_time(__func__, 1);
  thread t1(first_func);
  thread t2(second_func);

  t1.join();
  t2.join();
}

//==============================================================================
void cond_1() {
  std::lock_guard<mutex> lck(mtx);
  out_some_time(__func__, 3);
  t_cond.notify_one();
}

void cond_2() {
  out("1");
  std::unique_lock<mutex> u_lock(mtx);
  u_lock.unlock(); // fixme: why?
  out("2");
  t_cond.wait(u_lock);
  out_some_time(__func__, 1);
}

void test_thread_condition_variable_2() {
  out_some_time(__func__, 1);
  thread t2(cond_2);
  thread t1(cond_1);

  t1.join();
  t2.join();
}

void test_thread_condition_variable_3() {
  out_some_time(__func__, 1);
  thread t2(cond_2);
  thread t1(cond_1);

  t1.join();
  t2.join();
}

//==============================================================================
int main() { test_thread_condition_variable_3(); }
