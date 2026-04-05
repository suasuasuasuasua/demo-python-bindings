#include <pybind11/pybind11.h>

#include "myMathLib/numerics.h"

namespace py = pybind11;

PYBIND11_MODULE(_numerics, m) {
    m.doc() = "myMathLib._numerics: numerical utilities";

    m.def("round_to", &myMathLib::numerics::round_to, py::arg("x"), py::arg("decimals"),
          "Round x to the given number of decimal places");
    m.def("safe_sqrt", &myMathLib::numerics::safe_sqrt, py::arg("x"),
          "Square root that raises ValueError on negative input");
    m.def("safe_divide", &myMathLib::numerics::safe_divide, py::arg("a"), py::arg("b"),
          py::arg("fallback") = 0.0,
          "Divide a by b; returns fallback when denominator is near zero");
}
