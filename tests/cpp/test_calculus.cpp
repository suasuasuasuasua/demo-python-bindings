#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "myMathLib/calculus_ops.h"

static bool near_eq(double a, double b, double tol = 1e-4) {
    return std::abs(a - b) <= tol;
}

#define CHECK(expr) \
    do { \
        if (!(expr)) { \
            std::cerr << "FAIL [" << __func__ << "]: " #expr \
                      << " (" << __FILE__ << ":" << __LINE__ << ")\n"; \
            return false; \
        } \
    } while (0)

// f(x) = x^2  =>  f'(x) = 2x
static bool test_derivative() {
    auto square = [](double x) { return x * x; };
    CHECK(near_eq(myMathLib::calculus::derivative(square, 3.0), 6.0));
    CHECK(near_eq(myMathLib::calculus::derivative(square, 0.0), 0.0));
    CHECK(near_eq(myMathLib::calculus::derivative(square, -2.0), -4.0));

    try {
        myMathLib::calculus::derivative(square, 1.0, -1.0);
        std::cerr << "FAIL [" << __func__ << "]: expected exception for h <= 0\n";
        return false;
    } catch (const std::invalid_argument&) {}
    return true;
}

// integral of x from 0 to 1 = 0.5
static bool test_integrate() {
    auto identity = [](double x) { return x; };
    CHECK(near_eq(myMathLib::calculus::integrate(identity, 0.0, 1.0), 0.5));

    // integral of x^2 from 0 to 1 = 1/3
    auto square = [](double x) { return x * x; };
    CHECK(near_eq(myMathLib::calculus::integrate(square, 0.0, 1.0, 10000), 1.0 / 3.0));

    try {
        myMathLib::calculus::integrate(identity, 0.0, 1.0, 0);
        std::cerr << "FAIL [" << __func__ << "]: expected exception for n <= 0\n";
        return false;
    } catch (const std::invalid_argument&) {}
    return true;
}

int main() {
    struct { const char* name; bool (*fn)(); } tests[] = {
        { "derivative", test_derivative },
        { "integrate",  test_integrate  },
    };

    int failed = 0;
    for (auto& t : tests) {
        if (t.fn()) {
            std::cout << "PASS: " << t.name << "\n";
        } else {
            ++failed;
        }
    }

    if (failed) {
        std::cerr << failed << " test(s) failed.\n";
        return EXIT_FAILURE;
    }
    std::cout << "All tests passed.\n";
    return EXIT_SUCCESS;
}
