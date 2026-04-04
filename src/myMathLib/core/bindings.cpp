#include <pybind11/pybind11.h>

#include "myMathLib/math_ops.h"

namespace py = pybind11;

PYBIND11_MODULE(_core, m) {
    m.doc() = "myMathLib._core: core arithmetic operations";

    m.def("add", &myMathLib::add, py::arg("a"), py::arg("b"), "Add two numbers");
    m.def("subtract", &myMathLib::subtract, py::arg("a"), py::arg("b"), "Subtract b from a");
    m.def("multiply", &myMathLib::multiply, py::arg("a"), py::arg("b"), "Multiply two numbers");
    m.def("divide", &myMathLib::divide, py::arg("a"), py::arg("b"),
          "Divide a by b (raises ValueError on division by zero)");
    m.def("power", &myMathLib::power, py::arg("base"), py::arg("exponent"),
          "Raise base to the given exponent");
}
