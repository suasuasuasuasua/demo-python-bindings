import unittest
import myMathLib


class TestAdd(unittest.TestCase):
    def test_positive(self):
        self.assertAlmostEqual(myMathLib.add(3, 4), 7.0)

    def test_cancel(self):
        self.assertAlmostEqual(myMathLib.add(-1, 1), 0.0)

    def test_zeros(self):
        self.assertAlmostEqual(myMathLib.add(0, 0), 0.0)

    def test_negatives(self):
        self.assertAlmostEqual(myMathLib.add(-5, -3), -8.0)


class TestSubtract(unittest.TestCase):
    def test_basic(self):
        self.assertAlmostEqual(myMathLib.subtract(10, 3), 7.0)

    def test_negative_result(self):
        self.assertAlmostEqual(myMathLib.subtract(0, 5), -5.0)


class TestMultiply(unittest.TestCase):
    def test_positive(self):
        self.assertAlmostEqual(myMathLib.multiply(6, 7), 42.0)

    def test_negative(self):
        self.assertAlmostEqual(myMathLib.multiply(-2, 3), -6.0)

    def test_zero(self):
        self.assertAlmostEqual(myMathLib.multiply(0, 100), 0.0)


class TestDivide(unittest.TestCase):
    def test_exact(self):
        self.assertAlmostEqual(myMathLib.divide(15, 3), 5.0)

    def test_fraction(self):
        self.assertAlmostEqual(myMathLib.divide(1, 4), 0.25)

    def test_divide_by_zero(self):
        with self.assertRaises(ValueError):
            myMathLib.divide(1, 0)


class TestPower(unittest.TestCase):
    def test_integer_exponent(self):
        self.assertAlmostEqual(myMathLib.power(2, 8), 256.0)

    def test_zero_exponent(self):
        self.assertAlmostEqual(myMathLib.power(3, 0), 1.0)

    def test_negative_exponent(self):
        self.assertAlmostEqual(myMathLib.power(5, -1), 0.2)


class TestModule(unittest.TestCase):
    def test_docstring(self):
        self.assertIsNotNone(myMathLib.__doc__)
        self.assertGreater(len(myMathLib.__doc__), 0)


if __name__ == "__main__":
    unittest.main()
