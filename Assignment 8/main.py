import unittest
import random


class UnitTest(unittest.TestCase):
    def setUp(self):
        from module import random_divide, random_delay, get_split, static_func

        self.divide = random_divide
        self.delay = random_delay
        self.split = get_split
        self.static = static_func

    def test_divide_normal(self):
        self.assertEqual(self.divide(1, 2), 0.5)

    def test_divide_doc(self):
        self.assertEqual(self.divide.__doc__, "DIVIDE")

    def test_divide_error(self):
        self.assertEqual(self.divide(1, 0), None)

    def test_delay_doc(self):
        self.assertEqual(self.delay.__doc__, "DELAY")

    def test_delay_normal(self):
        for delay in (random.randint(0, 3) for _ in range(2)):
            self.assertAlmostEqual(self.delay(delay), delay, places=2)

    def test_column(self):
        from module import get_column, get_column2

        data = [[random.random() for _ in range(4)] for _ in range(5)]
        self.assertEqual(get_column(data, 1), get_column2(data, 1))

    def test_split(self):
        data = ["1 2 3 4", "5 6 7 8", "9 10 11 12"]
        self.assertEqual(self.split(data, 2), ["3", "7", "11"])

    def test_static(self):
        self.assertEqual(self.static(), 1)
        self.assertEqual(self.static(), 2)
        self.assertEqual(self.static(), 3)
    
    def test_static_doc(self):
        self.assertEqual(self.static.__doc__, "STATIC")

if __name__ == "__main__":
    unittest.main()
