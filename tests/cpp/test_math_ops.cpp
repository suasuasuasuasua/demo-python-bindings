#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <stdexcept>

#include "myMathLib/math_ops.h"

using Catch::Matchers::WithinRel;

TEST_CASE("add", "[math]") {
    REQUIRE_THAT(myMathLib::add(3.0, 4.0),   WithinRel(7.0));
    REQUIRE_THAT(myMathLib::add(-1.0, 1.0),  WithinRel(0.0, 1e-9));
    REQUIRE_THAT(myMathLib::add(0.0, 0.0),   WithinRel(0.0, 1e-9));
    REQUIRE_THAT(myMathLib::add(-5.0, -3.0), WithinRel(-8.0));
}

TEST_CASE("subtract", "[math]") {
    REQUIRE_THAT(myMathLib::subtract(10.0, 3.0), WithinRel(7.0));
    REQUIRE_THAT(myMathLib::subtract(0.0, 5.0),  WithinRel(-5.0));
}

TEST_CASE("multiply", "[math]") {
    REQUIRE_THAT(myMathLib::multiply(6.0, 7.0),   WithinRel(42.0));
    REQUIRE_THAT(myMathLib::multiply(-2.0, 3.0),  WithinRel(-6.0));
    REQUIRE_THAT(myMathLib::multiply(0.0, 100.0), WithinRel(0.0, 1e-9));
}

TEST_CASE("divide", "[math]") {
    REQUIRE_THAT(myMathLib::divide(15.0, 3.0), WithinRel(5.0));
    REQUIRE_THAT(myMathLib::divide(1.0, 4.0),  WithinRel(0.25));

    REQUIRE_THROWS_AS(myMathLib::divide(1.0, 0.0), std::invalid_argument);
}

TEST_CASE("power", "[math]") {
    REQUIRE_THAT(myMathLib::power(2.0, 8.0),  WithinRel(256.0));
    REQUIRE_THAT(myMathLib::power(3.0, 0.0),  WithinRel(1.0));
    REQUIRE_THAT(myMathLib::power(5.0, -1.0), WithinRel(0.2));
}
