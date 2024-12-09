#include "utils.h"

//=========================================================
void out_helloworld(int count) {
  while (count-- > 0) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    stringstream ss;
    ss << "{thread_id: " << std::this_thread::get_id() << "},";
    ss << "{context: helloworld}";
    out(ss.str());
  }
}

void thread_func() {
  std::thread t1{out_helloworld, 5};
  // t1.join();
  t1.detach();
  out_helloworld(1);
}

//=========================================================
struct HelloWorld {
  HelloWorld(int count) : count(count) {}

  void operator()() {
    out("[===start===] ", "{count: ", std::to_string(count), "}");
    while (count-- > 0) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      stringstream ss;
      ss << "{thread_id: " << std::this_thread::get_id() << "},";
      ss << "{context: helloworld}";
      out(ss.str());
    }
  }

  int count;
};

void thread_obj() {
  std::thread t1{HelloWorld(5)};
  t1.detach();
  out_helloworld(2);
}

void thread_obj2() {
  std::thread t1{HelloWorld(5)};
  std::thread t2{HelloWorld(1)};

  t1.join();
  t2.join();

  out_helloworld(2);
}

//=========================================================
int main() {
  // todo
  thread_obj2();
}
