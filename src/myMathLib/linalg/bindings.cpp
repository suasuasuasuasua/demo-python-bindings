#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "myMathLib/linalg_ops.h"

namespace py = pybind11;

PYBIND11_MODULE(_linalg, m) {
    m.doc() = "myMathLib.linalg._linalg: linear algebra operations (C++ extension)";

    m.def("dot", &myMathLib::linalg::dot, py::arg("a"), py::arg("b"),
          "Dot product of two equal-length vectors");
    m.def("norm", &myMathLib::linalg::norm, py::arg("v"),
          "Euclidean (L2) norm of a vector");
    m.def("cross", &myMathLib::linalg::cross, py::arg("a"), py::arg("b"),
          "Cross product of two 3-element vectors");
    m.def("matmul", &myMathLib::linalg::matmul, py::arg("A"), py::arg("B"),
          "Matrix multiplication of two 2-D lists (A @ B)");
}
