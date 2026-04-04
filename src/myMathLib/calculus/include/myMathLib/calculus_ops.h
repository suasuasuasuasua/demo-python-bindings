#pragma once

#include <functional>

#ifdef _WIN32
#ifdef CALCULUS_EXPORTS
#define CALCULUS_API __declspec(dllexport)
#else
#define CALCULUS_API __declspec(dllimport)
#endif
#else
#define CALCULUS_API __attribute__((visibility("default")))
#endif

namespace myMathLib::calculus {

// Numerical derivative using the central-difference formula.
CALCULUS_API double derivative(std::function<double(double)> f, double x, double h = 1e-5);

// Numerical integration using the composite trapezoidal rule.
CALCULUS_API double integrate(std::function<double(double)> f, double a, double b, int n = 1000);

// Adaptive integration that doubles the number of intervals until two
// successive estimates agree within tol (uses operators::approx_equal and
// numerics::safe_divide, exercising the shared-library dependency chain).
CALCULUS_API double converging_integrate(std::function<double(double)> f, double a, double b,
                                         double tol = 1e-6, int max_doublings = 20);

}  // namespace myMathLib::calculus
