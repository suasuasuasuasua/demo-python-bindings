#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "myMathLib/linalg_ops.h"

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

static bool test_dot() {
    CHECK(near_eq(myMathLib::linalg::dot({1, 2, 3}, {4, 5, 6}), 32.0));
    CHECK(near_eq(myMathLib::linalg::dot({1, 0}, {0, 1}), 0.0));
    CHECK(near_eq(myMathLib::linalg::dot({-1, -2}, {1, 2}), -5.0));
    try {
        myMathLib::linalg::dot({1, 2}, {1, 2, 3});
        std::cerr << "FAIL [" << __func__ << "]: expected exception for mismatched sizes\n";
        return false;
    } catch (const std::invalid_argument&) {}
    return true;
}

static bool test_norm() {
    CHECK(near_eq(myMathLib::linalg::norm({3, 4}), 5.0));
    CHECK(near_eq(myMathLib::linalg::norm({0, 0, 0}), 0.0));
    CHECK(near_eq(myMathLib::linalg::norm({1, 0, 0}), 1.0));
    return true;
}

static bool test_cross() {
    auto r = myMathLib::linalg::cross({1, 0, 0}, {0, 1, 0});
    CHECK(near_eq(r[0], 0.0));
    CHECK(near_eq(r[1], 0.0));
    CHECK(near_eq(r[2], 1.0));

    auto r2 = myMathLib::linalg::cross({0, 0, 1}, {0, 1, 0});
    CHECK(near_eq(r2[0], -1.0));
    CHECK(near_eq(r2[1],  0.0));
    CHECK(near_eq(r2[2],  0.0));

    try {
        myMathLib::linalg::cross({1, 2}, {3, 4});
        std::cerr << "FAIL [" << __func__ << "]: expected exception for non-3D vectors\n";
        return false;
    } catch (const std::invalid_argument&) {}
    return true;
}

static bool test_matmul() {
    std::vector<std::vector<double>> A = {{1, 2}, {3, 4}};
    std::vector<std::vector<double>> B = {{5, 6}, {7, 8}};
    auto C = myMathLib::linalg::matmul(A, B);
    CHECK(near_eq(C[0][0], 19.0));
    CHECK(near_eq(C[0][1], 22.0));
    CHECK(near_eq(C[1][0], 43.0));
    CHECK(near_eq(C[1][1], 50.0));

    try {
        myMathLib::linalg::matmul({{1, 2}}, {{1}, {2}, {3}});
        std::cerr << "FAIL [" << __func__ << "]: expected exception for incompatible dims\n";
        return false;
    } catch (const std::invalid_argument&) {}
    return true;
}

int main() {
    struct { const char* name; bool (*fn)(); } tests[] = {
        { "dot",    test_dot    },
        { "norm",   test_norm   },
        { "cross",  test_cross  },
        { "matmul", test_matmul },
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
