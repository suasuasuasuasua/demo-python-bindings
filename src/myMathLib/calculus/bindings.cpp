#include <pybind11/functional.h>
#include <pybind11/pybind11.h>

#include "myMathLib/calculus_ops.h"

namespace py = pybind11;

PYBIND11_MODULE(_calculus, m) {
    m.doc() = "myMathLib.calculus._calculus: numerical calculus operations (C++ extension)";

    m.def("derivative", &myMathLib::calculus::derivative, py::arg("f"), py::arg("x"),
          py::arg("h") = 1e-5,
          "Numerical derivative of f at x using the central-difference formula. "
          "h is the step size (default 1e-5).");
    m.def("integrate", &myMathLib::calculus::integrate, py::arg("f"), py::arg("a"), py::arg("b"),
          py::arg("n") = 1000,
          "Numerical integration of f over [a, b] using the composite trapezoidal rule. "
          "n is the number of sub-intervals (default 1000).");
    m.def("converging_integrate", &myMathLib::calculus::converging_integrate, py::arg("f"),
          py::arg("a"), py::arg("b"), py::arg("tol") = 1e-6, py::arg("max_doublings") = 20,
          "Adaptive trapezoidal integration that doubles sub-intervals until "
          "two successive estimates agree within tol.");
}
