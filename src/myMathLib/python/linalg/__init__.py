"""myMathLib.linalg: linear algebra operations.

Functions
---------
dot           -- dot product of two equal-length vectors
norm          -- Euclidean (L2) norm of a vector
cross         -- cross product of two 3-element vectors
matmul        -- matrix multiplication of two 2-D lists (A @ B)
angle_between -- angle in degrees between two vectors
"""

from ._linalg import angle_between, cross, dot, matmul, norm

__all__ = [
    "angle_between",
    "cross",
    "dot",
    "matmul",
    "norm",
]
