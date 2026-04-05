"""myMathLib.numerics: numerical utilities.

Functions
---------
round_to     -- round x to N decimal places
safe_sqrt    -- square root that raises ValueError on negative input
safe_divide  -- division that returns a fallback when the denominator is near zero
"""

import os
import pathlib

if os.name == "nt":
    # On Windows there is no RPATH.  The utility DLLs (myMathLib_numerics,
    # myMathLib_operators, myMathLib_constants) are installed one level up in
    # myMathLib/, so register that directory before importing.
    os.add_dll_directory(str(pathlib.Path(__file__).parent.parent))

from ._numerics import round_to, safe_divide, safe_sqrt

__all__ = [
    "round_to",
    "safe_sqrt",
    "safe_divide",
]
