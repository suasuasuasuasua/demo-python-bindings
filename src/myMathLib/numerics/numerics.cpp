#include "myMathLib/numerics.h"
#include "myMathLib/operators.h"

#include <cmath>
#include <stdexcept>

namespace myMathLib::numerics {

double round_to(double x, int decimals) {
    double factor = std::pow(10.0, decimals);
    return std::round(x * factor) / factor;
}

double safe_sqrt(double x) {
    if (x < 0.0) {
        throw std::invalid_argument("Cannot take square root of a negative number");
    }
    return std::sqrt(x);
}

double safe_divide(double a, double b, double fallback) {
    if (operators::approx_equal(b, 0.0)) {
        return fallback;
    }
    return a / b;
}

} // namespace myMathLib::numerics
