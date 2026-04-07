"""myMathLib.operators: utility operators.

Functions
---------
approx_equal       -- return True when |a - b| <= tol
clamp              -- clamp x to the closed interval [lo, hi]
lerp               -- linear interpolation between a and b
degrees_to_radians -- convert degrees to radians
radians_to_degrees -- convert radians to degrees
"""

import os
import pathlib

if os.name == "nt":
    # On Windows there is no RPATH.  myMathLib_operators.dll (and its dependency
    # myMathLib_constants.dll) are installed one level up in myMathLib/, so
    # register that directory before importing.
    os.add_dll_directory(str(pathlib.Path(__file__).parent.parent))

from ._operators import approx_equal, clamp, degrees_to_radians, lerp, radians_to_degrees

__all__ = [
    "approx_equal",
    "clamp",
    "lerp",
    "degrees_to_radians",
    "radians_to_degrees",
]
