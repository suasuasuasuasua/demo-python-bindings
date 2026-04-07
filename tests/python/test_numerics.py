import math
import unittest

import myMathLib.numerics as numerics


class TestRoundTo(unittest.TestCase):
    def test_two_decimals(self):
        self.assertAlmostEqual(numerics.round_to(3.14159, 2), 3.14)

    def test_zero_decimals(self):
        self.assertAlmostEqual(numerics.round_to(2.7, 0), 3.0)

    def test_negative_value(self):
        self.assertAlmostEqual(numerics.round_to(-1.005, 2), -1.0)

    def test_no_change(self):
        self.assertAlmostEqual(numerics.round_to(1.5, 4), 1.5)


class TestSafeSqrt(unittest.TestCase):
    def test_perfect_square(self):
        self.assertAlmostEqual(numerics.safe_sqrt(9.0), 3.0)

    def test_zero(self):
        self.assertAlmostEqual(numerics.safe_sqrt(0.0), 0.0)

    def test_irrational(self):
        self.assertAlmostEqual(numerics.safe_sqrt(2.0), math.sqrt(2), places=12)

    def test_negative_raises(self):
        with self.assertRaises(ValueError):
            numerics.safe_sqrt(-1.0)


class TestSafeDivide(unittest.TestCase):
    def test_exact(self):
        self.assertAlmostEqual(numerics.safe_divide(10.0, 2.0), 5.0)

    def test_fraction(self):
        self.assertAlmostEqual(numerics.safe_divide(1.0, 4.0), 0.25)

    def test_by_zero_default_fallback(self):
        self.assertAlmostEqual(numerics.safe_divide(5.0, 0.0), 0.0)

    def test_by_zero_custom_fallback(self):
        self.assertAlmostEqual(numerics.safe_divide(5.0, 0.0, -1.0), -1.0)

    def test_near_zero_denominator(self):
        self.assertAlmostEqual(numerics.safe_divide(1.0, 1e-15), 0.0)


class TestModule(unittest.TestCase):
    def test_docstring(self):
        self.assertIsNotNone(numerics.__doc__)
        self.assertGreater(len(numerics.__doc__), 0)


if __name__ == "__main__":
    unittest.main()
