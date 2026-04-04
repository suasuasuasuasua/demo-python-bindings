"""myMathLib: a math library with Python bindings via pybind11.

Sub-packages
------------
linalg   -- linear algebra (dot product, norm, cross product, matmul)
calculus -- numerical calculus (derivative, integrate)

Core arithmetic functions (add, subtract, multiply, divide, power) are
imported directly into this namespace for convenience.
"""

from ._core import add, divide, multiply, power, subtract
from . import calculus, linalg

__all__ = [
    "add",
    "subtract",
    "multiply",
    "divide",
    "power",
    "linalg",
    "calculus",
]
