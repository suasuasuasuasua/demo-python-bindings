#include <pybind11/pybind11.h>

#include "myMathLib/operators.h"

namespace py = pybind11;

PYBIND11_MODULE(_operators, m) {
    m.doc() = "myMathLib._operators: utility operators";

    m.def("approx_equal", &myMathLib::operators::approx_equal, py::arg("a"), py::arg("b"),
          py::arg("tol") = 1e-9, "Return True when |a - b| <= tol");
    m.def("clamp", &myMathLib::operators::clamp, py::arg("x"), py::arg("lo"), py::arg("hi"),
          "Clamp x to the closed interval [lo, hi]");
    m.def("lerp", &myMathLib::operators::lerp, py::arg("a"), py::arg("b"), py::arg("t"),
          "Linear interpolation: a + t * (b - a)");
    m.def("degrees_to_radians", &myMathLib::operators::degrees_to_radians, py::arg("deg"),
          "Convert an angle from degrees to radians");
    m.def("radians_to_degrees", &myMathLib::operators::radians_to_degrees, py::arg("rad"),
          "Convert an angle from radians to degrees");
}
