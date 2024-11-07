#!/usr/bin/env python3.10

import subprocess


class Command:
    def __init__(self, executable=None, *args):
        """
        Initialize Command with an executable and optional arguments.
        """
        self.executable = executable
        self.args = list(
            args
        )  # Convert args to a list for compatibility with subprocess

    def set_executable(self, executable):
        """
        Set the executable file for the command.
        """
        self.executable = executable

    def set_args(self, args):
        """
        Set the list of arguments for the command.
        """
        if isinstance(args, list):
            self.args = args
        else:
            raise TypeError("Args must be a list of arguments.")

    def run(self):
        """
        Execute the command and print stdout and stderr in real-time.
        """
        if self.executable is None:
            raise ValueError("Executable is not set.")

        # Combine the executable and arguments into a full command list
        command = [self.executable] + self.args

        try:
            # Start the subprocess and capture stdout and stderr in real-time
            process = subprocess.Popen(
                command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True
            )

            # Print output line by line as it's available
            for stdout_line in process.stdout:
                print(stdout_line, end="")  # Real-time output for stdout

            for stderr_line in process.stderr:
                print(stderr_line, end="")  # Real-time output for stderr

            # Wait for process to complete and get exit status
            process.wait()
            if process.returncode != 0:
                raise subprocess.CalledProcessError(process.returncode, command)

        except subprocess.CalledProcessError as e:
            print(f"Error: Command failed with return code {e.returncode}")
        except Exception as e:
            print(f"Error: {e}")


def check_black_format():
    pass


def check_static_analysis():
    pass


def run_all_check():
    check_black_format()
    check_static_analysis()


if __name__ == "__main__":
    pass
