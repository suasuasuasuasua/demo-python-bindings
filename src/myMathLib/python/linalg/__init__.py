"""myMathLib.linalg: linear algebra operations.

Functions
---------
dot    -- dot product of two equal-length vectors
norm   -- Euclidean (L2) norm of a vector
cross  -- cross product of two 3-element vectors
matmul -- matrix multiplication of two 2-D lists (A @ B)
"""

from ._linalg import *
from . import _linalg as _ext

# Derive __all__ from the extension module so new C++ symbols are
# automatically re-exported without updating this file.
__all__ = [name for name in dir(_ext) if not name.startswith("_")]
del _ext
