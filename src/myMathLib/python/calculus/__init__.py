"""myMathLib.calculus: numerical calculus operations.

Functions
---------
derivative           -- numerical derivative using the central-difference formula
integrate            -- numerical integration using the composite trapezoidal rule
converging_integrate -- adaptive trapezoidal integration that refines until convergence
"""

import os
import pathlib

if os.name == "nt":
    # On Windows there is no RPATH.  The shared utility DLLs (numerics,
    # operators, constants) are installed one level up in the myMathLib/
    # directory.  Register that directory so the loader can find them before
    # the extension module (_calculus.pyd) is imported.
    os.add_dll_directory(str(pathlib.Path(__file__).parent.parent))

from ._calculus import converging_integrate, derivative, integrate

__all__ = [
    "converging_integrate",
    "derivative",
    "integrate",
]
