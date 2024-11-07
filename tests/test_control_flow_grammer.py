import unittest
from enum import Enum

class Color(Enum):
    Red = "red"
    Yellow = "yellow"
    Blue = "blue"


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

    def test_enum_statement(self):
        color = Color("red")

        match color:
            case Color.Red:
                self.assertEqual(color, Color.Red, "color is red")

        match color:
            case Color.Blue:
                self.assertNotEqual(color, Color.Blue, "color is red, not blue")
            case _:
                self.assertEqual("_", "_", "color match default")

        match color:
            case Color.Red if False:
                self.assertEqual(color, Color.Red, "test \"case expression if condition expression\": color is red")
            case Color.Red if True:
                self.assertEqual(color, Color.Red, "test \"case expression if condition expression\": color is red")



if __name__ == "__main__":
     unittest.main()

