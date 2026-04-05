#include <pybind11/pybind11.h>

#include "myMathLib/constants.h"

namespace py = pybind11;

PYBIND11_MODULE(_constants, m) {
    m.doc() = "myMathLib._constants: mathematical constants";

    m.def("pi", &myMathLib::constants::pi, "Pi (3.14159...)");
    m.def("e", &myMathLib::constants::e, "Euler's number (2.71828...)");
    m.def("sqrt2", &myMathLib::constants::sqrt2, "Square root of 2 (1.41421...)");
    m.def("golden_ratio", &myMathLib::constants::golden_ratio, "Golden ratio (1.61803...)");
}
