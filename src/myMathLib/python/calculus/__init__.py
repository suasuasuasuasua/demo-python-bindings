"""myMathLib.calculus: numerical calculus operations.

Functions
---------
derivative -- numerical derivative using the central-difference formula
integrate  -- numerical integration using the composite trapezoidal rule
"""

from ._calculus import derivative, integrate

__all__ = [
    "derivative",
    "integrate",
]
