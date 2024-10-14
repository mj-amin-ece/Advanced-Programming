import unittest
import aphw6

class Test(unittest.TestCase):
    def test1(self):
        with open('a.jpg', 'rb') as file:
            b1 = file.read()
        aphw6.code('a.jpg', lambda x: 255 - x)
        with open('a.jpg', 'rb') as file:
            b2 = file.read()
        self.assertEqual(b1[5], 255-b2[5])

    def test2(self):
        fact = aphw6.Factorial()
        x = fact(5)
        self.assertEqual(x, 120)
        self.assertEqual(fact.dict[3], 6)

if __name__=='__main__':
    unittest.main()
