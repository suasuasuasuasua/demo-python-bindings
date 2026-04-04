#include "myMathLib/linalg_ops.h"

#include <cmath>
#include <stdexcept>

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

double norm(const std::vector<double>& v) {
    return std::sqrt(dot(v, v));
}

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

std::vector<std::vector<double>> matmul(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B)
{
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

} // namespace myMathLib::linalg
