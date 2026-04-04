#pragma once

#include <stdexcept>
#include <vector>

#ifdef _WIN32
#ifdef LINALG_EXPORTS
#define LINALG_API __declspec(dllexport)
#else
#define LINALG_API __declspec(dllimport)
#endif
#else
#define LINALG_API __attribute__((visibility("default")))
#endif

namespace myMathLib::linalg {

LINALG_API double dot(const std::vector<double>& a, const std::vector<double>& b);
LINALG_API double norm(const std::vector<double>& v);
LINALG_API std::vector<double> cross(const std::vector<double>& a, const std::vector<double>& b);
LINALG_API std::vector<std::vector<double>> matmul(const std::vector<std::vector<double>>& A,
                                                   const std::vector<std::vector<double>>& B);

// Returns the angle between two vectors in degrees.
// Uses numerics::safe_divide and operators::radians_to_degrees (which uses
// constants::pi()), exercising the full shared-library dependency chain.
LINALG_API double angle_between(const std::vector<double>& a, const std::vector<double>& b);

}  // namespace myMathLib::linalg
