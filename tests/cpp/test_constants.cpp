#include <gtest/gtest.h>

#include "myMathLib/constants.h"

TEST(Pi, Value) { EXPECT_DOUBLE_EQ(myMathLib::constants::pi(), 3.14159265358979323846); }

TEST(E, Value) { EXPECT_DOUBLE_EQ(myMathLib::constants::e(), 2.71828182845904523536); }

TEST(Sqrt2, Value) { EXPECT_DOUBLE_EQ(myMathLib::constants::sqrt2(), 1.41421356237309504880); }

TEST(GoldenRatio, Value) {
    EXPECT_DOUBLE_EQ(myMathLib::constants::golden_ratio(), 1.61803398874989484820);
}

TEST(Pi, IsPositive) { EXPECT_GT(myMathLib::constants::pi(), 0.0); }

TEST(E, IsPositive) { EXPECT_GT(myMathLib::constants::e(), 0.0); }

TEST(Sqrt2, SquaredIsTwo) {
    double s = myMathLib::constants::sqrt2();
    EXPECT_NEAR(s * s, 2.0, 1e-12);
}

TEST(GoldenRatio, PhiRelation) {
    // golden_ratio^2 == golden_ratio + 1
    double phi = myMathLib::constants::golden_ratio();
    EXPECT_NEAR(phi * phi, phi + 1.0, 1e-12);
}
