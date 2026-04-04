#include "myMathLib/linalg_ops.h"

#include <cmath>
#include <stdexcept>

#include "myMathLib/numerics.h"
#include "myMathLib/operators.h"

namespace myMathLib::linalg {

double dot(const std::vector<double>& a, const std::vector<double>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vectors must have the same length");
    }
    double result = 0.0;
    for (std::size_t i = 0; i < a.size(); ++i) {
        result += a[i] * b[i];
    }
    return result;
}

double norm(const std::vector<double>& v) { return std::sqrt(dot(v, v)); }

std::vector<double> cross(const std::vector<double>& a, const std::vector<double>& b) {
    if (a.size() != 3 || b.size() != 3) {
        throw std::invalid_argument("Cross product requires 3-element vectors");
    }
    return {
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0],
    };
}

std::vector<std::vector<double>> matmul(const std::vector<std::vector<double>>& A,
                                        const std::vector<std::vector<double>>& B) {
    if (A.empty() || B.empty()) {
        throw std::invalid_argument("Matrices must be non-empty");
    }
    const std::size_t rows = A.size();
    const std::size_t inner = A[0].size();
    const std::size_t cols = B[0].size();
    if (inner != B.size()) {
        throw std::invalid_argument("Matrix dimensions are incompatible for multiplication");
    }
    std::vector<std::vector<double>> C(rows, std::vector<double>(cols, 0.0));
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t k = 0; k < inner; ++k) {
            for (std::size_t j = 0; j < cols; ++j) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

}  // namespace myMathLib::linalg

namespace myMathLib::linalg {

double angle_between(const std::vector<double>& a, const std::vector<double>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vectors must have the same length");
    }
    // safe_divide (from numerics) returns 0 when the denominator is ~0.
    // Clamping to [-1, 1] guards against floating-point values that drift
    // just outside that range, which would make acos return NaN.
    double cos_angle = numerics::safe_divide(dot(a, b), norm(a) * norm(b));
    cos_angle = operators::clamp(cos_angle, -1.0, 1.0);
    return operators::radians_to_degrees(std::acos(cos_angle));
}

}  // namespace myMathLib::linalg