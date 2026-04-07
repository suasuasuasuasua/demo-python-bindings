import math
import unittest

import myMathLib.operators as operators


class TestApproxEqual(unittest.TestCase):
    def test_equal_values(self):
        self.assertTrue(operators.approx_equal(1.0, 1.0))

    def test_within_default_tolerance(self):
        self.assertTrue(operators.approx_equal(1.0, 1.0 + 1e-10))

    def test_outside_default_tolerance(self):
        self.assertFalse(operators.approx_equal(1.0, 1.0 + 1e-8))

    def test_custom_tolerance(self):
        self.assertTrue(operators.approx_equal(1.0, 1.1, 0.2))
        self.assertFalse(operators.approx_equal(1.0, 1.3, 0.2))


class TestClamp(unittest.TestCase):
    def test_below_low(self):
        self.assertAlmostEqual(operators.clamp(-5.0, 0.0, 10.0), 0.0)

    def test_above_high(self):
        self.assertAlmostEqual(operators.clamp(15.0, 0.0, 10.0), 10.0)

    def test_in_range(self):
        self.assertAlmostEqual(operators.clamp(5.0, 0.0, 10.0), 5.0)


class TestLerp(unittest.TestCase):
    def test_at_zero(self):
        self.assertAlmostEqual(operators.lerp(0.0, 10.0, 0.0), 0.0)

    def test_at_one(self):
        self.assertAlmostEqual(operators.lerp(0.0, 10.0, 1.0), 10.0)

    def test_at_midpoint(self):
        self.assertAlmostEqual(operators.lerp(0.0, 10.0, 0.5), 5.0)


class TestDegreesToRadians(unittest.TestCase):
    def test_zero(self):
        self.assertAlmostEqual(operators.degrees_to_radians(0.0), 0.0)

    def test_half_circle(self):
        self.assertAlmostEqual(operators.degrees_to_radians(180.0), math.pi, places=12)

    def test_full_circle(self):
        self.assertAlmostEqual(operators.degrees_to_radians(360.0), 2 * math.pi, places=12)


class TestRadiansToDegrees(unittest.TestCase):
    def test_zero(self):
        self.assertAlmostEqual(operators.radians_to_degrees(0.0), 0.0)

    def test_pi(self):
        self.assertAlmostEqual(operators.radians_to_degrees(math.pi), 180.0, places=12)

    def test_roundtrip(self):
        angle = 45.0
        self.assertAlmostEqual(
            operators.radians_to_degrees(operators.degrees_to_radians(angle)),
            angle,
            places=12,
        )


class TestModule(unittest.TestCase):
    def test_docstring(self):
        self.assertIsNotNone(operators.__doc__)
        self.assertGreater(len(operators.__doc__), 0)


if __name__ == "__main__":
    unittest.main()
