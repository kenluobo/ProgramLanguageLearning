import unittest


class TestBuiltInDataStructure(unittest.TestCase):
    def test_list_comprehension(self):
        target_lst = [0, 10, 20]

        first_lst = list(map(lambda x: x * 10, range(3)))
        self.assertEqual(
            first_lst,
            target_lst,
            "use first list comprehension: list(map(lambda-expression, range-expression))",
        )

        second_lst = [x * 10 for x in range(3)]
        self.assertEqual(
            second_lst,
            target_lst,
            "use second list comprehension: [expression for parameter in range-expression]",
        )

    def test_iterate_skill_1(self):
        # iterate and get key and value from dict
        id_to_name = {1: "a", 2: "b", 3: "c"}
        id2name_str = "1:a 2:b 3:c"
        result: str = ""
        size = len(id_to_name)
        count: int = 0
        for key, value in id_to_name.items():
            count += 1
            result += "{KEY}:{VALUE}".format(KEY=str(key), VALUE=value)
            if count < size:
                result += " "
        self.assertEqual(id2name_str, result)

    def test_iterate_skill_2(self):
        # iterate and get key and value from dict
        id_to_name = {1: "a", 2: "b", 3: "c"}
        # id2name_str = "0:1 1:2 2:3"
        id2name_str = "0:(1, 'a') 1:(2, 'b') 2:(3, 'c')"
        result: str = ""
        size = len(id_to_name)
        count: int = 0
        for key, value in enumerate(
            id_to_name.items()
        ):  # it's different from test_iterate_skill_1
            count += 1
            result += "{KEY}:{VALUE}".format(KEY=str(key), VALUE=value)
            if count < size:
                result += " "
        self.assertEqual(id2name_str, result)

    def test_iterate_skill_3(self):
        first_lst = [0, 1, 2]
        second_lst = ["zero", "one", "two"]
        result = dict()
        for key, value in zip(first_lst, second_lst):
            result[key] = value

        target_dict: dict = {0: "zero", 1: "one", 2: "two"}
        self.assertDictEqual(
            result, target_dict, "test zip function and compare result and target dict"
        )


if __name__ == "__main__":
    unittest.main()
