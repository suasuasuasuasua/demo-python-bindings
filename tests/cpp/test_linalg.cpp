#include <gtest/gtest.h>

#include "myMathLib/linalg_ops.h"

TEST(Dot, Basic) { EXPECT_DOUBLE_EQ(myMathLib::linalg::dot({1, 2, 3}, {4, 5, 6}), 32.0); }

TEST(Dot, Orthogonal) { EXPECT_DOUBLE_EQ(myMathLib::linalg::dot({1, 0}, {0, 1}), 0.0); }

TEST(Dot, Negative) { EXPECT_DOUBLE_EQ(myMathLib::linalg::dot({-1, -2}, {1, 2}), -5.0); }

TEST(Dot, MismatchedSizesThrows) {
    EXPECT_THROW(myMathLib::linalg::dot({1, 2}, {1, 2, 3}), std::invalid_argument);
}

TEST(Norm, ThreeFourFive) { EXPECT_DOUBLE_EQ(myMathLib::linalg::norm({3, 4}), 5.0); }

TEST(Norm, ZeroVector) { EXPECT_DOUBLE_EQ(myMathLib::linalg::norm({0, 0, 0}), 0.0); }

TEST(Norm, UnitVector) { EXPECT_DOUBLE_EQ(myMathLib::linalg::norm({1, 0, 0}), 1.0); }

TEST(Cross, XCrossY) {
    auto r = myMathLib::linalg::cross({1, 0, 0}, {0, 1, 0});
    EXPECT_DOUBLE_EQ(r[0], 0.0);
    EXPECT_DOUBLE_EQ(r[1], 0.0);
    EXPECT_DOUBLE_EQ(r[2], 1.0);
}

TEST(Cross, Anticommutative) {
    auto r1 = myMathLib::linalg::cross({1, 2, 3}, {4, 5, 6});
    auto r2 = myMathLib::linalg::cross({4, 5, 6}, {1, 2, 3});
    for (std::size_t i = 0; i < 3; ++i) {
        EXPECT_DOUBLE_EQ(r1[i], -r2[i]);
    }
}

TEST(Cross, Non3DVectorsThrows) {
    EXPECT_THROW(myMathLib::linalg::cross({1, 2}, {3, 4}), std::invalid_argument);
}

TEST(Matmul, TwoByTwo) {
    std::vector<std::vector<double>> A = {{1, 2}, {3, 4}};
    std::vector<std::vector<double>> B = {{5, 6}, {7, 8}};
    auto C = myMathLib::linalg::matmul(A, B);
    EXPECT_DOUBLE_EQ(C[0][0], 19.0);
    EXPECT_DOUBLE_EQ(C[0][1], 22.0);
    EXPECT_DOUBLE_EQ(C[1][0], 43.0);
    EXPECT_DOUBLE_EQ(C[1][1], 50.0);
}

TEST(Matmul, Identity) {
    std::vector<std::vector<double>> I = {{1, 0}, {0, 1}};
    std::vector<std::vector<double>> A = {{3, 7}, {2, 5}};
    auto C = myMathLib::linalg::matmul(A, I);
    EXPECT_DOUBLE_EQ(C[0][0], 3.0);
    EXPECT_DOUBLE_EQ(C[0][1], 7.0);
    EXPECT_DOUBLE_EQ(C[1][0], 2.0);
    EXPECT_DOUBLE_EQ(C[1][1], 5.0);
}

TEST(Matmul, IncompatibleDimsThrows) {
    EXPECT_THROW(myMathLib::linalg::matmul({{1, 2}}, {{1}, {2}, {3}}), std::invalid_argument);
}

TEST(AngleBetween, Orthogonal) {
    // 90 degrees between x-axis and y-axis
    EXPECT_NEAR(myMathLib::linalg::angle_between({1, 0}, {0, 1}), 90.0, 1e-9);
}

TEST(AngleBetween, Parallel) {
    // 0 degrees between identical vectors
    EXPECT_NEAR(myMathLib::linalg::angle_between({1, 2, 3}, {1, 2, 3}), 0.0, 1e-9);
}

TEST(AngleBetween, Antiparallel) {
    // 180 degrees between opposite vectors
    EXPECT_NEAR(myMathLib::linalg::angle_between({1, 0}, {-1, 0}), 180.0, 1e-9);
}

TEST(AngleBetween, MismatchedSizesThrows) {
    EXPECT_THROW(myMathLib::linalg::angle_between({1, 2}, {1, 2, 3}), std::invalid_argument);
}
