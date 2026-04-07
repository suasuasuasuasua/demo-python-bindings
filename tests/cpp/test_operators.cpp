#include <gtest/gtest.h>

#include "myMathLib/constants.h"
#include "myMathLib/operators.h"

TEST(ApproxEqual, EqualValues) { EXPECT_TRUE(myMathLib::operators::approx_equal(1.0, 1.0)); }

TEST(ApproxEqual, WithinDefaultTolerance) {
    EXPECT_TRUE(myMathLib::operators::approx_equal(1.0, 1.0 + 1e-10));
}

TEST(ApproxEqual, OutsideDefaultTolerance) {
    EXPECT_FALSE(myMathLib::operators::approx_equal(1.0, 1.0 + 1e-8));
}

TEST(ApproxEqual, CustomTolerance) {
    EXPECT_TRUE(myMathLib::operators::approx_equal(1.0, 1.1, 0.2));
    EXPECT_FALSE(myMathLib::operators::approx_equal(1.0, 1.3, 0.2));
}

TEST(Clamp, BelowLow) { EXPECT_DOUBLE_EQ(myMathLib::operators::clamp(-5.0, 0.0, 10.0), 0.0); }

TEST(Clamp, AboveHigh) { EXPECT_DOUBLE_EQ(myMathLib::operators::clamp(15.0, 0.0, 10.0), 10.0); }

TEST(Clamp, InRange) { EXPECT_DOUBLE_EQ(myMathLib::operators::clamp(5.0, 0.0, 10.0), 5.0); }

TEST(Lerp, AtZero) { EXPECT_DOUBLE_EQ(myMathLib::operators::lerp(0.0, 10.0, 0.0), 0.0); }

TEST(Lerp, AtOne) { EXPECT_DOUBLE_EQ(myMathLib::operators::lerp(0.0, 10.0, 1.0), 10.0); }

TEST(Lerp, AtMidpoint) { EXPECT_DOUBLE_EQ(myMathLib::operators::lerp(0.0, 10.0, 0.5), 5.0); }

TEST(DegreesToRadians, Zero) {
    EXPECT_DOUBLE_EQ(myMathLib::operators::degrees_to_radians(0.0), 0.0);
}

TEST(DegreesToRadians, HalfCircle) {
    EXPECT_NEAR(myMathLib::operators::degrees_to_radians(180.0), myMathLib::constants::pi(), 1e-12);
}

TEST(DegreesToRadians, FullCircle) {
    EXPECT_NEAR(myMathLib::operators::degrees_to_radians(360.0), 2.0 * myMathLib::constants::pi(),
                1e-12);
}

TEST(RadiansToDegrees, Zero) {
    EXPECT_DOUBLE_EQ(myMathLib::operators::radians_to_degrees(0.0), 0.0);
}

TEST(RadiansToDegrees, Pi) {
    EXPECT_NEAR(myMathLib::operators::radians_to_degrees(myMathLib::constants::pi()), 180.0, 1e-12);
}

TEST(RadiansToDegrees, Roundtrip) {
    double angle = 45.0;
    EXPECT_NEAR(
        myMathLib::operators::radians_to_degrees(myMathLib::operators::degrees_to_radians(angle)),
        angle, 1e-12);
}
