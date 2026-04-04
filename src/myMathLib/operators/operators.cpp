#include "myMathLib/operators.h"

#include <cmath>

#include "myMathLib/constants.h"

namespace myMathLib::operators {

bool approx_equal(double a, double b, double tol) { return std::abs(a - b) <= tol; }

double clamp(double x, double lo, double hi) { return x < lo ? lo : (x > hi ? hi : x); }

double lerp(double a, double b, double t) { return a + t * (b - a); }

double degrees_to_radians(double deg) { return deg * constants::pi() / 180.0; }

double radians_to_degrees(double rad) { return rad * 180.0 / constants::pi(); }

}  // namespace myMathLib::operators
