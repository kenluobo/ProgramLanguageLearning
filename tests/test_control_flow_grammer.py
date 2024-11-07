#!/usr/bin/env python3

import unittest


class TestControlFlowStatement(unittest.TestCase):

    def test_for_range_statement(self):
        words = ["cat", "window", "defenestrate"]
        words_str = " ".join(words)

        target_words_str: str = ""
        count: int = len(words)
        it_time: int = 0
        for word in words:
            it_time += 1

            target_words_str += word
            if it_time != count:
                target_words_str += " "

        self.assertEqual(
            target_words_str, words_str, "fail to generate target_words_str"
        )


if __name__ == "__main__":
     unittest.main()

