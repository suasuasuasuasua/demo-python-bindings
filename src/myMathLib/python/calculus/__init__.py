"""myMathLib.calculus: numerical calculus operations.

Functions
---------
derivative -- numerical derivative using the central-difference formula
integrate  -- numerical integration using the composite trapezoidal rule
"""

from ._calculus import *
from . import _calculus as _ext

# Derive __all__ from the extension module so new C++ symbols are
# automatically re-exported without updating this file.
__all__ = [name for name in dir(_ext) if not name.startswith("_")]
del _ext
