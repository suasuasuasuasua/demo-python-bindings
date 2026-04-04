#include "myMathLib/calculus_ops.h"
#include "myMathLib/numerics.h"
#include "myMathLib/operators.h"

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

namespace myMathLib::calculus {

double converging_integrate(
    std::function<double(double)> f, double a, double b,
    double tol, int max_doublings)
{
    if (tol <= 0.0) {
        throw std::invalid_argument("tol must be positive");
    }
    if (max_doublings <= 0) {
        throw std::invalid_argument("max_doublings must be positive");
    }
    // Compute width via safe_divide so that a == b returns 0 cleanly.
    if (operators::approx_equal(a, b, tol)) {
        return 0.0;
    }
    int n = 1;
    double prev = integrate(f, a, b, n);
    for (int i = 0; i < max_doublings; ++i) {
        n *= 2;
        double curr = integrate(f, a, b, n);
        // Use safe_divide (numerics) for a relative-error check to avoid
        // division by zero when the integral is very close to zero.
        double scale = numerics::safe_divide(std::abs(curr - prev),
                                             std::abs(curr) + 1.0);
        if (operators::approx_equal(scale, 0.0, tol)) {
            return curr;
        }
        prev = curr;
    }
    return prev;
}

} // namespace myMathLib::calculus
