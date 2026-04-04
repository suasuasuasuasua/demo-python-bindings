#pragma once

#include <cstddef>

#ifdef _WIN32
#ifdef NUMERICS_EXPORTS
#define NUMERICS_API __declspec(dllexport)
#else
#define NUMERICS_API __declspec(dllimport)
#endif
#else
#define NUMERICS_API __attribute__((visibility("default")))
#endif

namespace myMathLib::numerics {

// Rounds x to the given number of decimal places.
NUMERICS_API double round_to(double x, int decimals);

// Square root that throws on negative input instead of returning NaN.
NUMERICS_API double safe_sqrt(double x);

// Division that returns fallback when the denominator is near zero.
NUMERICS_API double safe_divide(double a, double b, double fallback = 0.0);

}  // namespace myMathLib::numerics
