"""myMathLib.constants: mathematical constants.

Functions
---------
pi            -- Pi (3.14159...)
e             -- Euler's number (2.71828...)
sqrt2         -- Square root of 2 (1.41421...)
golden_ratio  -- Golden ratio (1.61803...)
"""

import os
import pathlib

if os.name == "nt":
    # On Windows there is no RPATH.  myMathLib_constants.dll is installed one
    # level up in myMathLib/, so register that directory before importing.
    os.add_dll_directory(str(pathlib.Path(__file__).parent.parent))

from ._constants import e, golden_ratio, pi, sqrt2

__all__ = [
    "pi",
    "e",
    "sqrt2",
    "golden_ratio",
]
