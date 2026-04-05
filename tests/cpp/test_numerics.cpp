#include <gtest/gtest.h>

#include "myMathLib/numerics.h"

TEST(RoundTo, TwoDecimals) {
    EXPECT_DOUBLE_EQ(myMathLib::numerics::round_to(3.14159, 2), 3.14);
}

TEST(RoundTo, ZeroDecimals) {
    EXPECT_DOUBLE_EQ(myMathLib::numerics::round_to(2.7, 0), 3.0);
}

TEST(RoundTo, NegativeValue) {
    EXPECT_DOUBLE_EQ(myMathLib::numerics::round_to(-1.005, 2), -1.01);
}

TEST(RoundTo, NoChange) {
    EXPECT_DOUBLE_EQ(myMathLib::numerics::round_to(1.5, 4), 1.5);
}

TEST(SafeSqrt, PerfectSquare) {
    EXPECT_DOUBLE_EQ(myMathLib::numerics::safe_sqrt(9.0), 3.0);
}

TEST(SafeSqrt, Zero) {
    EXPECT_DOUBLE_EQ(myMathLib::numerics::safe_sqrt(0.0), 0.0);
}

TEST(SafeSqrt, Irrational) {
    EXPECT_NEAR(myMathLib::numerics::safe_sqrt(2.0), 1.41421356237, 1e-9);
}

TEST(SafeSqrt, NegativeThrows) {
    EXPECT_THROW(myMathLib::numerics::safe_sqrt(-1.0), std::invalid_argument);
}

TEST(SafeDivide, Exact) {
    EXPECT_DOUBLE_EQ(myMathLib::numerics::safe_divide(10.0, 2.0), 5.0);
}

TEST(SafeDivide, Fraction) {
    EXPECT_DOUBLE_EQ(myMathLib::numerics::safe_divide(1.0, 4.0), 0.25);
}

TEST(SafeDivide, ByZeroDefaultFallback) {
    EXPECT_DOUBLE_EQ(myMathLib::numerics::safe_divide(5.0, 0.0), 0.0);
}

TEST(SafeDivide, ByZeroCustomFallback) {
    EXPECT_DOUBLE_EQ(myMathLib::numerics::safe_divide(5.0, 0.0, -1.0), -1.0);
}

TEST(SafeDivide, NearZeroDenominator) {
    EXPECT_DOUBLE_EQ(myMathLib::numerics::safe_divide(1.0, 1e-15), 0.0);
}
