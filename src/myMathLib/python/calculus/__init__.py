"""myMathLib.calculus: numerical calculus operations.

Functions
---------
derivative           -- numerical derivative using the central-difference formula
integrate            -- numerical integration using the composite trapezoidal rule
converging_integrate -- adaptive trapezoidal integration that refines until convergence
"""

from ._calculus import converging_integrate, derivative, integrate

__all__ = [
    "converging_integrate",
    "derivative",
    "integrate",
]
