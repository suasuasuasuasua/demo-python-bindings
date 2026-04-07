"""myMathLib: a math library with Python bindings via pybind11.

Sub-packages
------------
constants -- mathematical constants (pi, e, sqrt2, golden_ratio)
operators -- utility operators (approx_equal, clamp, lerp, angle conversions)
numerics  -- numerical utilities (round_to, safe_sqrt, safe_divide)
linalg    -- linear algebra (dot product, norm, cross product, matmul)
calculus  -- numerical calculus (derivative, integrate)

Core arithmetic functions (add, subtract, multiply, divide, power) are
imported directly into this namespace for convenience.
"""

from . import calculus, constants, linalg, numerics, operators
from ._core import add, divide, multiply, power, subtract

__all__ = [
    "add",
    "subtract",
    "multiply",
    "divide",
    "power",
    "constants",
    "operators",
    "numerics",
    "linalg",
    "calculus",
]
