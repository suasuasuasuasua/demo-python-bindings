#include <cmath>

#include <gtest/gtest.h>
#include "myMathLib/calculus_ops.h"

TEST(Derivative, SquareAt3) {
    // d/dx x^2 at x=3 should be 6
    EXPECT_NEAR(myMathLib::calculus::derivative([](double x) { return x * x; }, 3.0), 6.0, 1e-4);
}

TEST(Derivative, SquareAtZero) {
    EXPECT_NEAR(myMathLib::calculus::derivative([](double x) { return x * x; }, 0.0), 0.0, 1e-4);
}

TEST(Derivative, SquareNegative) {
    EXPECT_NEAR(myMathLib::calculus::derivative([](double x) { return x * x; }, -2.0), -4.0, 1e-4);
}

TEST(Derivative, Sin) {
    // d/dx sin(x) at x=0 should be cos(0) = 1
    EXPECT_NEAR(myMathLib::calculus::derivative([](double x) { return std::sin(x); }, 0.0), 1.0, 1e-4);
}

TEST(Derivative, NegativeStepThrows) {
    EXPECT_THROW(
        myMathLib::calculus::derivative([](double x) { return x; }, 1.0, -1.0),
        std::invalid_argument
    );
}

TEST(Integrate, Constant) {
    // integral of 1 from 0 to 5 = 5
    EXPECT_NEAR(myMathLib::calculus::integrate([](double) { return 1.0; }, 0.0, 5.0), 5.0, 1e-4);
}

TEST(Integrate, Linear) {
    // integral of x from 0 to 1 = 0.5
    EXPECT_NEAR(myMathLib::calculus::integrate([](double x) { return x; }, 0.0, 1.0), 0.5, 1e-4);
}

TEST(Integrate, Quadratic) {
    // integral of x^2 from 0 to 1 = 1/3
    EXPECT_NEAR(
        myMathLib::calculus::integrate([](double x) { return x * x; }, 0.0, 1.0, 10000),
        1.0 / 3.0, 1e-4
    );
}

TEST(Integrate, SinOverPi) {
    // integral of sin(x) from 0 to pi = 2
    EXPECT_NEAR(myMathLib::calculus::integrate([](double x) { return std::sin(x); }, 0.0, M_PI, 10000), 2.0, 1e-4);
}

TEST(Integrate, ZeroIntervalsThrows) {
    EXPECT_THROW(
        myMathLib::calculus::integrate([](double x) { return x; }, 0.0, 1.0, 0),
        std::invalid_argument
    );
}

