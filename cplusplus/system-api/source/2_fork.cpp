#include <sys/wait.h>
#include <unistd.h>

#include <iostream>

int main() {
  if (const pid_t pid = fork(); pid < 0) {
    std::cerr << "Failed to fork." << std::endl;
  } else if (pid == 0) {
    execl("/bin/ls", "ls", "-l", nullptr);
  } else {
    wait(nullptr);
    std::cout << "Child process finished." << std::endl;
  }

  return 0;
}
