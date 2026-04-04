import math
import unittest

import myMathLib.linalg as linalg


class TestDot(unittest.TestCase):
    def test_basic(self):
        self.assertAlmostEqual(linalg.dot([1, 2, 3], [4, 5, 6]), 32.0)

    def test_orthogonal(self):
        self.assertAlmostEqual(linalg.dot([1, 0], [0, 1]), 0.0)

    def test_negative(self):
        self.assertAlmostEqual(linalg.dot([-1, -2], [1, 2]), -5.0)

    def test_mismatched_raises(self):
        with self.assertRaises(Exception):
            linalg.dot([1, 2], [1, 2, 3])


class TestNorm(unittest.TestCase):
    def test_345_triangle(self):
        self.assertAlmostEqual(linalg.norm([3, 4]), 5.0)

    def test_zero_vector(self):
        self.assertAlmostEqual(linalg.norm([0, 0, 0]), 0.0)

    def test_unit_vector(self):
        self.assertAlmostEqual(linalg.norm([1, 0, 0]), 1.0)


class TestCross(unittest.TestCase):
    def test_x_cross_y(self):
        r = linalg.cross([1, 0, 0], [0, 1, 0])
        self.assertAlmostEqual(r[0], 0.0)
        self.assertAlmostEqual(r[1], 0.0)
        self.assertAlmostEqual(r[2], 1.0)

    def test_anticommutative(self):
        r1 = linalg.cross([1, 2, 3], [4, 5, 6])
        r2 = linalg.cross([4, 5, 6], [1, 2, 3])
        for a, b in zip(r1, r2):
            self.assertAlmostEqual(a, -b)

    def test_non_3d_raises(self):
        with self.assertRaises(Exception):
            linalg.cross([1, 2], [3, 4])


class TestMatmul(unittest.TestCase):
    def test_2x2(self):
        A = [[1, 2], [3, 4]]
        B = [[5, 6], [7, 8]]
        C = linalg.matmul(A, B)
        self.assertAlmostEqual(C[0][0], 19.0)
        self.assertAlmostEqual(C[0][1], 22.0)
        self.assertAlmostEqual(C[1][0], 43.0)
        self.assertAlmostEqual(C[1][1], 50.0)

    def test_identity(self):
        I = [[1, 0], [0, 1]]
        A = [[3, 7], [2, 5]]
        C = linalg.matmul(A, I)
        self.assertAlmostEqual(C[0][0], 3.0)
        self.assertAlmostEqual(C[0][1], 7.0)
        self.assertAlmostEqual(C[1][0], 2.0)
        self.assertAlmostEqual(C[1][1], 5.0)

    def test_incompatible_raises(self):
        with self.assertRaises(Exception):
            linalg.matmul([[1, 2]], [[1], [2], [3]])


class TestAngleBetween(unittest.TestCase):
    def test_orthogonal(self):
        self.assertAlmostEqual(linalg.angle_between([1, 0], [0, 1]), 90.0)

    def test_parallel(self):
        self.assertAlmostEqual(linalg.angle_between([1, 2, 3], [1, 2, 3]), 0.0)

    def test_antiparallel(self):
        self.assertAlmostEqual(linalg.angle_between([1, 0], [-1, 0]), 180.0)

    def test_mismatched_raises(self):
        with self.assertRaises(Exception):
            linalg.angle_between([1, 2], [1, 2, 3])


class TestModule(unittest.TestCase):
    def test_docstring(self):
        self.assertIsNotNone(linalg.__doc__)
        self.assertGreater(len(linalg.__doc__), 0)


if __name__ == "__main__":
    unittest.main()
