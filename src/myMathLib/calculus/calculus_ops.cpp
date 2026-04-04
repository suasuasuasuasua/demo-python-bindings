#include "myMathLib/calculus_ops.h"

#include <stdexcept>

namespace myMathLib::calculus {

double derivative(std::function<double(double)> f, double x, double h) {
    if (h <= 0.0) {
        throw std::invalid_argument("Step size h must be positive");
    }
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

double integrate(std::function<double(double)> f, double a, double b, int n) {
    if (n <= 0) {
        throw std::invalid_argument("Number of intervals n must be positive");
    }
    const double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; ++i) {
        sum += f(a + i * h);
    }
    return sum * h;
}

} // namespace myMathLib::calculus
