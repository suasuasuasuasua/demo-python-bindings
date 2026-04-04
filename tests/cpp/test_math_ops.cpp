#include <gtest/gtest.h>

#include "myMathLib/math_ops.h"

TEST(Add, Positive) { EXPECT_DOUBLE_EQ(myMathLib::add(3.0, 4.0), 7.0); }

TEST(Add, Cancel) { EXPECT_DOUBLE_EQ(myMathLib::add(-1.0, 1.0), 0.0); }

TEST(Add, Zeros) { EXPECT_DOUBLE_EQ(myMathLib::add(0.0, 0.0), 0.0); }

TEST(Add, Negatives) { EXPECT_DOUBLE_EQ(myMathLib::add(-5.0, -3.0), -8.0); }

TEST(Subtract, Basic) { EXPECT_DOUBLE_EQ(myMathLib::subtract(10.0, 3.0), 7.0); }

TEST(Subtract, NegativeResult) { EXPECT_DOUBLE_EQ(myMathLib::subtract(0.0, 5.0), -5.0); }

TEST(Multiply, Positive) { EXPECT_DOUBLE_EQ(myMathLib::multiply(6.0, 7.0), 42.0); }

TEST(Multiply, Negative) { EXPECT_DOUBLE_EQ(myMathLib::multiply(-2.0, 3.0), -6.0); }

TEST(Multiply, Zero) { EXPECT_DOUBLE_EQ(myMathLib::multiply(0.0, 100.0), 0.0); }

TEST(Divide, Exact) { EXPECT_DOUBLE_EQ(myMathLib::divide(15.0, 3.0), 5.0); }

TEST(Divide, Fraction) { EXPECT_DOUBLE_EQ(myMathLib::divide(1.0, 4.0), 0.25); }

TEST(Divide, ByZeroThrows) { EXPECT_THROW(myMathLib::divide(1.0, 0.0), std::invalid_argument); }

TEST(Power, IntegerExponent) { EXPECT_DOUBLE_EQ(myMathLib::power(2.0, 8.0), 256.0); }

TEST(Power, ZeroExponent) { EXPECT_DOUBLE_EQ(myMathLib::power(3.0, 0.0), 1.0); }

TEST(Power, NegativeExponent) { EXPECT_NEAR(myMathLib::power(5.0, -1.0), 0.2, 1e-12); }
