#pragma once

#include <functional>

#ifdef _WIN32
#  ifdef CALCULUS_EXPORTS
#    define CALCULUS_API __declspec(dllexport)
#  else
#    define CALCULUS_API __declspec(dllimport)
#  endif
#else
#  define CALCULUS_API __attribute__((visibility("default")))
#endif

namespace myMathLib::calculus {

// Numerical derivative using the central-difference formula.
CALCULUS_API double derivative(std::function<double(double)> f, double x, double h = 1e-5);

// Numerical integration using the composite trapezoidal rule.
CALCULUS_API double integrate(std::function<double(double)> f, double a, double b, int n = 1000);

} // namespace myMathLib::calculus
