# demo-python-bindings

A dummy math library written in C++ with Python bindings using [pybind11](https://pybind11.readthedocs.io/) and [scikit-build-core](https://scikit-build-core.readthedocs.io/).

## Project Structure

```
demo-python-bindings/
├── CMakeLists.txt                        # Root CMake — delegates to sub-libraries
├── pyproject.toml                        # Python packaging via scikit-build-core
├── src/
│   └── myMathLib/
│       ├── core/                         # Core arithmetic (add, subtract, …)
│       │   ├── CMakeLists.txt
│       │   ├── include/myMathLib/math_ops.h
│       │   ├── math_ops.cpp
│       │   └── bindings.cpp              # → myMathLib._core extension
│       ├── linalg/                       # Linear algebra (dot, norm, cross, matmul)
│       │   ├── CMakeLists.txt
│       │   ├── include/myMathLib/linalg_ops.h
│       │   ├── linalg_ops.cpp
│       │   └── bindings.cpp              # → myMathLib.linalg extension
│       ├── calculus/                     # Numerical calculus (derivative, integrate)
│       │   ├── CMakeLists.txt
│       │   ├── include/myMathLib/calculus_ops.h
│       │   ├── calculus_ops.cpp
│       │   └── bindings.cpp              # → myMathLib.calculus extension
│       └── python/
│           └── __init__.py               # Python package init (re-exports core functions)
└── tests/
    ├── cpp/                              # C++ unit tests (one per sub-library)
    └── python/                           # Python unit tests (one per sub-library)
```

### Installed wheel layout

```
myMathLib/
├── __init__.py               # re-exports core functions; imports linalg & calculus
├── _core.cpython-XY.so       # pybind11 extension for core arithmetic
├── libmyMathLib_core.so      # underlying C++ shared library
├── linalg.cpython-XY.so      # pybind11 extension for linalg
├── libmyMathLib_linalg.so    # underlying C++ shared library
├── calculus.cpython-XY.so    # pybind11 extension for calculus
└── libmyMathLib_calculus.so  # underlying C++ shared library
```

All C++ shared libraries live *in the same directory* as the extension modules.
On Linux/macOS each extension uses `RPATH "$ORIGIN"` / `"@loader_path"` to find
its dependency without any extra `PATH` or `LD_LIBRARY_PATH` configuration.
On Windows, Python 3.8+ automatically adds the extension's directory to the DLL
search path, so the `.dll` files are found automatically.

## Building & Installing

### Prerequisites

- Python 3.8+
- CMake 3.17+
- A C++17-compatible compiler (MSVC on Windows, GCC/Clang on Linux/macOS)

### Install the Python package

```bash
pip install .
```

## Usage

```python
import myMathLib

# Core arithmetic — available directly on the package
myMathLib.add(3, 4)        # 7.0
myMathLib.subtract(10, 3)  # 7.0
myMathLib.multiply(6, 7)   # 42.0
myMathLib.divide(15, 3)    # 5.0
myMathLib.power(2, 8)      # 256.0

# Linear algebra sub-package
import myMathLib.linalg as linalg

linalg.dot([1, 2, 3], [4, 5, 6])          # 32.0
linalg.norm([3, 4])                        # 5.0
linalg.cross([1, 0, 0], [0, 1, 0])        # [0.0, 0.0, 1.0]
linalg.matmul([[1, 2], [3, 4]],
              [[5, 6], [7, 8]])             # [[19, 22], [43, 50]]

# Calculus sub-package
import myMathLib.calculus as calculus

calculus.derivative(lambda x: x**2, 3.0)  # ~6.0  (central difference)
calculus.integrate(lambda x: x, 0.0, 1.0) # ~0.5  (trapezoidal rule)
```

## Available API

### `myMathLib` (core arithmetic)

| Function | Description |
|---|---|
| `add(a, b)` | Returns `a + b` |
| `subtract(a, b)` | Returns `a - b` |
| `multiply(a, b)` | Returns `a * b` |
| `divide(a, b)` | Returns `a / b`; raises `ValueError` on division by zero |
| `power(base, exponent)` | Returns `base ** exponent` |

### `myMathLib.linalg`

| Function | Description |
|---|---|
| `dot(a, b)` | Dot product of two equal-length vectors |
| `norm(v)` | Euclidean (L2) norm of a vector |
| `cross(a, b)` | Cross product of two 3-element vectors |
| `matmul(A, B)` | Matrix multiplication (`A @ B`) of two 2-D lists |

### `myMathLib.calculus`

| Function | Description |
|---|---|
| `derivative(f, x, h=1e-5)` | Numerical derivative of `f` at `x` via central differences |
| `integrate(f, a, b, n=1000)` | Numerical integral of `f` over `[a, b]` via the trapezoidal rule |

## Architecture

Each sub-library follows the same pattern:

1. **`myMathLib_<name>`** — A C++ shared library (`.so` / `.dll`) with the implementation.
2. **`<name>.cpython-XY.so`** — A pybind11 Python extension that links to the shared library.

The root `CMakeLists.txt` handles global settings and then delegates to
`src/myMathLib/{core,linalg,calculus}/CMakeLists.txt` via `add_subdirectory`.
Each sub-`CMakeLists.txt` owns its library, extension, and C++ tests independently.