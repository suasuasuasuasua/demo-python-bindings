import math
import unittest

import myMathLib.constants as constants


class TestPi(unittest.TestCase):
    def test_value(self):
        self.assertAlmostEqual(constants.pi(), math.pi, places=15)

    def test_is_positive(self):
        self.assertGreater(constants.pi(), 0.0)


class TestE(unittest.TestCase):
    def test_value(self):
        self.assertAlmostEqual(constants.e(), math.e, places=15)

    def test_is_positive(self):
        self.assertGreater(constants.e(), 0.0)


class TestSqrt2(unittest.TestCase):
    def test_value(self):
        self.assertAlmostEqual(constants.sqrt2(), math.sqrt(2), places=15)

    def test_squared_is_two(self):
        s = constants.sqrt2()
        self.assertAlmostEqual(s * s, 2.0, places=12)


class TestGoldenRatio(unittest.TestCase):
    def test_value(self):
        self.assertAlmostEqual(constants.golden_ratio(), (1 + math.sqrt(5)) / 2, places=14)

    def test_phi_relation(self):
        # phi^2 == phi + 1
        phi = constants.golden_ratio()
        self.assertAlmostEqual(phi * phi, phi + 1.0, places=12)


class TestModule(unittest.TestCase):
    def test_docstring(self):
        self.assertIsNotNone(constants.__doc__)
        self.assertGreater(len(constants.__doc__), 0)


if __name__ == "__main__":
    unittest.main()
