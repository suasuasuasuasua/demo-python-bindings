#pragma once

#ifdef _WIN32
#ifdef OPERATORS_EXPORTS
#define OPERATORS_API __declspec(dllexport)
#else
#define OPERATORS_API __declspec(dllimport)
#endif
#else
#define OPERATORS_API __attribute__((visibility("default")))
#endif

namespace myMathLib::operators {

// Returns true when |a - b| <= tol.
OPERATORS_API bool approx_equal(double a, double b, double tol = 1e-9);

// Clamps x to [lo, hi].
OPERATORS_API double clamp(double x, double lo, double hi);

// Linear interpolation: a + t*(b - a).
OPERATORS_API double lerp(double a, double b, double t);

// Angle unit conversions (use constants::pi() internally).
OPERATORS_API double degrees_to_radians(double deg);
OPERATORS_API double radians_to_degrees(double rad);

}  // namespace myMathLib::operators
