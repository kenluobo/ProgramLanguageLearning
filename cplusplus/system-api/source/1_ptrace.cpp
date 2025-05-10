#include <fmt/format.h>
#include <sys/ptrace.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cerrno>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

constexpr long kExecveSyscall = SYS_execve;

std::string readCString(pid_t pid, unsigned long address) {
  std::string result;
  while (true) {
    errno = 0;
    const long data = ptrace(PTRACE_PEEKDATA, pid, address, nullptr);
    if (data == -1 && errno != 0) {
      break;
    }

    for (int i = 0; i < sizeof(long); ++i) {
      const char byte = static_cast<char>((data >> (i * 8)) & 0xFF);
      if (byte == '\0') {
        return result;
      }
      result += byte;
    }

    address += sizeof(long);
  }
  return result;
}

std::vector<std::string> readCStringArray(pid_t pid, unsigned long address) {
  std::vector<std::string> arguments;
  while (true) {
    errno = 0;
    const unsigned long argPtr = ptrace(PTRACE_PEEKDATA, pid, address, nullptr);
    if (argPtr == 0 ||
        (argPtr == static_cast<unsigned long>(-1) && errno != 0)) {
      break;
    }
    arguments.push_back(readCString(pid, argPtr));
    address += sizeof(unsigned long);
  }
  return arguments;
}

void printExecveInfo(pid_t pid, unsigned long filenamePtr,
                     unsigned long argvPtr) {
  const std::string path = readCString(pid, filenamePtr);
  const std::vector<std::string> args = readCStringArray(pid, argvPtr);

  std::ostringstream oss;
  for (std::size_t pos = 0, size = args.size(); pos < size; ++pos) {
    if (pos < (size - 1)) {
      oss << fmt::format("{}, ", args[pos]);
    } else {
      oss << args[pos];
    }
  }

  oss << fmt::format("{{ func_name: {}, pid: {}, args: [{}] }}\n", "execve}", pid,
                     oss.str());

  std::cout << oss.str();
}

void runChildProcess(char* executable, char* const* args) {
  if (ptrace(PTRACE_TRACEME, 0, nullptr, nullptr) < 0) {
    std::perror("ptrace TRACEME");
    std::exit(EXIT_FAILURE);
  }

  kill(getpid(), SIGSTOP);

  execvp(executable, args);
  std::perror("execvp failed");
  std::exit(EXIT_FAILURE);
}

void traceSyscalls(pid_t childPid) {
  int status;
  bool inSyscall = false;
  long lastSyscall = -1;

  while (true) {
    if (waitpid(childPid, &status, 0) < 0) {
      std::perror("waitpid");
      break;
    }

    if (WIFEXITED(status) || WIFSIGNALED(status)) {
      break;
    }

    if (!(WIFSTOPPED(status) && WSTOPSIG(status) == (SIGTRAP | 0x80))) {
      ptrace(PTRACE_SYSCALL, childPid, nullptr, nullptr);
      continue;
    }

    user_regs_struct regs{};
    if (ptrace(PTRACE_GETREGS, childPid, nullptr, &regs) != 0) {
      std::perror("ptrace GETREGS");
      break;
    }

#if defined(__x86_64__)
    if (!inSyscall && regs.orig_rax == kExecveSyscall) {
      if (lastSyscall != regs.rip) {  // 防止重复打印
        printExecveInfo(childPid, regs.rdi, regs.rsi);
        lastSyscall = regs.rip;
      }
    }
#else
#error "Only x86_64 supported"
#endif

    inSyscall = !inSyscall;
    ptrace(PTRACE_SYSCALL, childPid, nullptr, nullptr);
  }
}

}  // namespace

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <program> [args...]\n";
    return EXIT_FAILURE;
  }

  const pid_t childPid = fork();
  if (childPid == 0) {
    runChildProcess(argv[1], &argv[1]);
  } else if (childPid > 0) {
    int status = 0;
    if (waitpid(childPid, &status, 0) < 0) {
      std::perror("waitpid");
      return EXIT_FAILURE;
    }

    if (!WIFSTOPPED(status) || WSTOPSIG(status) != SIGSTOP) {
      std::cerr << "Child did not stop as expected.\n";
      return EXIT_FAILURE;
    }

    if (ptrace(PTRACE_SETOPTIONS, childPid, nullptr, PTRACE_O_TRACESYSGOOD) !=
        0) {
      std::perror("ptrace SETOPTIONS");
      return EXIT_FAILURE;
    }

    ptrace(PTRACE_SYSCALL, childPid, nullptr, nullptr);

    traceSyscalls(childPid);
  } else {
    std::perror("fork");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

