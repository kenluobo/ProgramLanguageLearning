#!/usr/bin/env python3

import unittest
import os
import argparse


def parse_args():
    parser = argparse.ArgumentParser(
            prog="test tool",
            description="load all test case and run unit test",
            epilog="note: you must run on /path/to/learn-python/tests or specify test-dir"
            )

    parser.add_argument(
            "-d",
            "--dir",
            required=False,
            type=str,
            dest="test_dir",
            default=".",
            metavar="test-dir",
            help="The directory path that store test file. Default is current directory"
            )

    parser.add_argument(
            "--verbosity",
            "-v",
            required=False,
            type=int,
            choices=[1, 2],
            dest="verbosity",
            default=1,
            metavar=1,
            help="Increment output verbosity"
            )

    return parser.parse_args()


def run_test(args):
    loader = unittest.TestLoader()

    work_dir = args.test_dir
    file_name_pattern = "test*.py"
    suite = loader.discover(start_dir=work_dir, pattern=file_name_pattern)

    v_level=args.verbosity
    runner = unittest.TextTestRunner(verbosity=v_level)
    runner.run(suite)


def main():
    args = parse_args()
    run_test(args)
    

if __name__ == "__main__":
    main()

