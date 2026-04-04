#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "myMathLib/math_ops.h"

// Returns true when |a - b| is within rel_tol of |b| (or abs_tol for near-zero values).
static bool near_eq(double a, double b, double rel_tol = 1e-9, double abs_tol = 1e-12) {
    return std::abs(a - b) <= std::max(rel_tol * std::max(std::abs(a), std::abs(b)), abs_tol);
}

#define CHECK(expr) \
    do { \
        if (!(expr)) { \
            std::cerr << "FAIL [" << __func__ << "]: " #expr \
                      << " (" << __FILE__ << ":" << __LINE__ << ")\n"; \
            return false; \
        } \
    } while (0)

static bool test_add() {
    CHECK(near_eq(myMathLib::add(3.0, 4.0),   7.0));
    CHECK(near_eq(myMathLib::add(-1.0, 1.0),  0.0));
    CHECK(near_eq(myMathLib::add(0.0, 0.0),   0.0));
    CHECK(near_eq(myMathLib::add(-5.0, -3.0), -8.0));
    return true;
}

static bool test_subtract() {
    CHECK(near_eq(myMathLib::subtract(10.0, 3.0), 7.0));
    CHECK(near_eq(myMathLib::subtract(0.0, 5.0),  -5.0));
    return true;
}

static bool test_multiply() {
    CHECK(near_eq(myMathLib::multiply(6.0, 7.0),   42.0));
    CHECK(near_eq(myMathLib::multiply(-2.0, 3.0),  -6.0));
    CHECK(near_eq(myMathLib::multiply(0.0, 100.0), 0.0));
    return true;
}

static bool test_divide() {
    CHECK(near_eq(myMathLib::divide(15.0, 3.0), 5.0));
    CHECK(near_eq(myMathLib::divide(1.0, 4.0),  0.25));
    try {
        myMathLib::divide(1.0, 0.0);
        std::cerr << "FAIL [" << __func__ << "]: expected exception for divide by zero\n";
        return false;
    } catch (const std::invalid_argument&) {}
    return true;
}

static bool test_power() {
    CHECK(near_eq(myMathLib::power(2.0, 8.0),  256.0));
    CHECK(near_eq(myMathLib::power(3.0, 0.0),  1.0));
    CHECK(near_eq(myMathLib::power(5.0, -1.0), 0.2));
    return true;
}

int main() {
    struct { const char* name; bool (*fn)(); } tests[] = {
        { "add",      test_add      },
        { "subtract", test_subtract },
        { "multiply", test_multiply },
        { "divide",   test_divide   },
        { "power",    test_power    },
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
