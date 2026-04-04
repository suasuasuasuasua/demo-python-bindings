#include "myMathLib/math_ops.h"

#include <cmath>
#include <limits>
#include <stdexcept>

namespace myMathLib {

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (std::abs(b) < std::numeric_limits<double>::epsilon()) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}

double power(double base, double exponent) {
    return std::pow(base, exponent);
}

} // namespace myMathLib
