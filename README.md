# demo-python-bindings

A dummy math library written in C++ with Python bindings using [pybind11](https://pybind11.readthedocs.io/) and [scikit-build-core](https://scikit-build-core.readthedocs.io/).

## Project Structure

```
demo-python-bindings/
├── CMakeLists.txt                        # CMake build system (C++17, shared library + pybind11 extension)
├── pyproject.toml                        # Python packaging via scikit-build-core
└── src/
    └── myMathLib/
        ├── include/
        │   └── myMathLib/
        │       └── math_ops.h            # Public C++ API header
        ├── math_ops.cpp                  # C++ library implementation
        └── bindings.cpp                  # pybind11 Python bindings
```

## Building & Installing

### Prerequisites

- Python 3.8+
- CMake 3.17+
- A C++17-compatible compiler (MSVC on Windows, GCC/Clang on Linux/macOS)

### Install the Python package

```bash
pip install .
```

Or for development (editable install):

```bash
pip install --no-build-isolation -e .
```

## Usage

```python
import myMathLib

myMathLib.add(3, 4)        # 7.0
myMathLib.subtract(10, 3)  # 7.0
myMathLib.multiply(6, 7)   # 42.0
myMathLib.divide(15, 3)    # 5.0
myMathLib.power(2, 8)      # 256.0
```

## Available Functions

| Function | Description |
|---|---|
| `add(a, b)` | Returns `a + b` |
| `subtract(a, b)` | Returns `a - b` |
| `multiply(a, b)` | Returns `a * b` |
| `divide(a, b)` | Returns `a / b`; raises `ValueError` on division by zero |
| `power(base, exponent)` | Returns `base ** exponent` |

## Architecture

- **`myMathLib_core`** — A C++ shared library (`.so` / `.dll`) built with C++17 containing the actual math implementations.
- **`myMathLib`** — A pybind11 Python extension module that links to `myMathLib_core` and exposes the API to Python.

The extension module uses `$ORIGIN` (Linux) / `@loader_path` (macOS) RPATH so it can locate `myMathLib_core` at runtime without any extra configuration.