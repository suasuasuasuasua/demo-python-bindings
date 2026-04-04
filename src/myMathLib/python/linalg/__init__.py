"""myMathLib.linalg: linear algebra operations.

Functions
---------
dot           -- dot product of two equal-length vectors
norm          -- Euclidean (L2) norm of a vector
cross         -- cross product of two 3-element vectors
matmul        -- matrix multiplication of two 2-D lists (A @ B)
angle_between -- angle in degrees between two vectors
"""

import os
import pathlib

if os.name == "nt":
    # On Windows there is no RPATH.  The shared utility DLLs (numerics,
    # operators, constants) are installed one level up in the myMathLib/
    # directory.  Register that directory so the loader can find them before
    # the extension module (_linalg.pyd) is imported.
    os.add_dll_directory(str(pathlib.Path(__file__).parent.parent))

from ._linalg import angle_between, cross, dot, matmul, norm

__all__ = [
    "angle_between",
    "cross",
    "dot",
    "matmul",
    "norm",
]
