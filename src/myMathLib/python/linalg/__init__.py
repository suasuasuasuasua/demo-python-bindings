"""myMathLib.linalg: linear algebra operations.

Functions
---------
dot    -- dot product of two equal-length vectors
norm   -- Euclidean (L2) norm of a vector
cross  -- cross product of two 3-element vectors
matmul -- matrix multiplication of two 2-D lists (A @ B)
"""

from ._linalg import cross, dot, matmul, norm

__all__ = [
    "cross",
    "dot",
    "matmul",
    "norm",
]
