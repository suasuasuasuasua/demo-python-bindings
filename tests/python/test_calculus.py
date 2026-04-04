import math
import unittest

import myMathLib.calculus as calculus


class TestDerivative(unittest.TestCase):
    def test_square_at_3(self):
        # d/dx x^2 at x=3 should be 6
        result = calculus.derivative(lambda x: x**2, 3.0)
        self.assertAlmostEqual(result, 6.0, places=4)

    def test_square_at_zero(self):
        result = calculus.derivative(lambda x: x**2, 0.0)
        self.assertAlmostEqual(result, 0.0, places=4)

    def test_square_negative(self):
        result = calculus.derivative(lambda x: x**2, -2.0)
        self.assertAlmostEqual(result, -4.0, places=4)

    def test_sin(self):
        # d/dx sin(x) at x=0 should be cos(0) = 1
        result = calculus.derivative(math.sin, 0.0)
        self.assertAlmostEqual(result, 1.0, places=4)

    def test_invalid_step_raises(self):
        with self.assertRaises(Exception):
            calculus.derivative(lambda x: x, 1.0, -1.0)


class TestIntegrate(unittest.TestCase):
    def test_constant(self):
        # integral of 1 from 0 to 5 = 5
        result = calculus.integrate(lambda x: 1.0, 0.0, 5.0)
        self.assertAlmostEqual(result, 5.0, places=4)

    def test_linear(self):
        # integral of x from 0 to 1 = 0.5
        result = calculus.integrate(lambda x: x, 0.0, 1.0)
        self.assertAlmostEqual(result, 0.5, places=4)

    def test_quadratic(self):
        # integral of x^2 from 0 to 1 = 1/3
        result = calculus.integrate(lambda x: x**2, 0.0, 1.0, 10000)
        self.assertAlmostEqual(result, 1.0 / 3.0, places=4)

    def test_sin_over_pi(self):
        # integral of sin(x) from 0 to pi = 2
        result = calculus.integrate(math.sin, 0.0, math.pi, 10000)
        self.assertAlmostEqual(result, 2.0, places=4)

    def test_invalid_n_raises(self):
        with self.assertRaises(Exception):
            calculus.integrate(lambda x: x, 0.0, 1.0, 0)


class TestConvergingIntegrate(unittest.TestCase):
    def test_constant(self):
        result = calculus.converging_integrate(lambda x: 1.0, 0.0, 5.0)
        self.assertAlmostEqual(result, 5.0, places=4)

    def test_linear(self):
        result = calculus.converging_integrate(lambda x: x, 0.0, 1.0)
        self.assertAlmostEqual(result, 0.5, places=4)

    def test_equal_bounds_is_zero(self):
        result = calculus.converging_integrate(lambda x: x, 2.0, 2.0)
        self.assertAlmostEqual(result, 0.0, places=9)

    def test_invalid_tol_raises(self):
        with self.assertRaises(Exception):
            calculus.converging_integrate(lambda x: x, 0.0, 1.0, -1.0)


class TestModule(unittest.TestCase):
    def test_docstring(self):
        self.assertIsNotNone(calculus.__doc__)
        self.assertGreater(len(calculus.__doc__), 0)


if __name__ == "__main__":
    unittest.main()
