#include "utils.h"

//==============================================================================
int run_cmd(const string &cmd) {
  // int status = cmd.size() % 2;
  int status = std::system(cmd.c_str());
  if (status == 0) {
    out_and_wait<1>("[running] ", cmd);
  } else {
    out_and_wait<3>("[running] ", cmd);
  }
  return status;
}

void run_cmds(const std::vector<string> &cmds) {
  for (const auto &cmd : cmds) {
    stringstream ss;
    std::future<int> task = std::async(std::launch::async, run_cmd, cmd);
    const auto duration = std::chrono::seconds(2);
    if (task.wait_for(duration) == std::future_status::timeout) {
      ss << "cmd timeout: " << cmd;
      out(ss.str());
      continue;
    }

    ss << "cmd success: " << cmd << "; return number: " << task.get();
    out(ss.str());
  }
}

void test_future_and_wait_for() {
  const std::vector<string> cmds = {"cmd1 ", "cmd2", "cmd3 "};
  run_cmds(cmds);
}

//==============================================================================
int main() { test_future_and_wait_for(); }
