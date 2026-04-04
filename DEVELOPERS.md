# Developer Guide

This document covers build dependencies and environment setup for all supported platforms.

## Table of Contents

- [Quick Start](#quick-start)
- [dev.py — Build Script](#devpy--build-script)
- [Windows](#windows)
- [Linux](#linux)
- [Linux → Windows Cross-Compile (MinGW)](#linux--windows-cross-compile-mingw)
- [macOS](#macos)
- [CMake Options](#cmake-options)

---

## Quick Start

### Python package (all platforms)

```bash
pip install scikit-build-core pybind11
pip install --no-build-isolation .
```

### C++ tests only (all platforms)

```bash
cmake -B build -DBUILD_PYTHON_BINDINGS=OFF -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

GoogleTest is fetched automatically via CMake `FetchContent` — no manual install required.

---

## dev.py — Build Script

`dev.py` is a convenience wrapper around CMake and the test runners. It does not replace CMake — it calls the same commands documented in the platform sections below.

```
python dev.py <subcommand> [options]
```

### `build`

Configure and build with CMake.

```bash
# Default: Release build with Python bindings, no tests
python dev.py build

# Debug build, C++ tests enabled, no Python bindings
python dev.py build --build-type Debug --tests --no-python-bindings

# Custom build directory
python dev.py build -d build-release

# MinGW cross-compile (Linux → Windows)
python dev.py build \
  -d build-mingw \
  --no-python-bindings \
  --tests \
  --toolchain cmake/toolchains/mingw-w64-x86_64.cmake \
  --emulator "$(which wine64 2>/dev/null || which wine)"

# Pass extra flags directly to cmake
python dev.py build -- -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64"
```

| Flag | Default | Description |
|---|---|---|
| `-d`, `--build-dir` | `build` | CMake build directory |
| `-t`, `--build-type` | `Release` | `Release`, `Debug`, `RelWithDebInfo`, `MinSizeRel` |
| `--no-python-bindings` | — | Disable pybind11 extension targets |
| `--tests` | off | Enable C++ GoogleTest targets |
| `--toolchain FILE` | — | CMake toolchain file (e.g. MinGW) |
| `--emulator BIN` | — | `CMAKE_CROSSCOMPILING_EMULATOR` (e.g. Wine) |
| `--` | — | Remaining args forwarded verbatim to `cmake` |

### `test`

Run C++ tests via `ctest` and/or Python tests via `unittest`.

```bash
# Run both C++ and Python tests
python dev.py test

# C++ tests only, verbose
python dev.py test --cpp-only --verbose

# Python tests only
python dev.py test --python-only

# Cross-compile build (suppresses Wine debug noise)
python dev.py test -d build-mingw --cpp-only --winedebug
```

| Flag | Default | Description |
|---|---|---|
| `-d`, `--build-dir` | `build` | Build directory to run `ctest` from |
| `-t`, `--build-type` | `Release` | Build config passed to `ctest -C` |
| `--cpp-only` | — | Skip Python tests |
| `--python-only` | — | Skip `ctest` |
| `-v`, `--verbose` | — | Pass `-V` to `ctest` |
| `--winedebug` | — | Set `WINEDEBUG=-all` (suppress Wine output) |

### `clean`

Remove build directories and Python cache artifacts.

```bash
# Remove ./build (default)
python dev.py clean

# Remove a specific build directory
python dev.py clean --dirs build-mingw

# Remove multiple directories
python dev.py clean --dirs build build-mingw

# Skip __pycache__ / .egg-info / dist cleanup
python dev.py clean --keep-py
```

| Flag | Default | Description |
|---|---|---|
| `--dirs` | `build` | One or more directories to delete |
| `--keep-py` | — | Do not remove Python cache/dist artifacts |

### `format`

Format C++ sources with `clang-format` and Python files with `isort` + `black`. Style is configured in `.clang-format` and `pyproject.toml` (`[tool.black]`, `[tool.isort]`).

```bash
# Format everything in-place
python dev.py format

# Check only (non-zero exit if anything would change — useful in CI)
python dev.py format --check

# C++ only
python dev.py format --cpp-only

# Python only
python dev.py format --python-only
```

| Flag | Default | Description |
|---|---|---|
| `--check` | — | Dry-run; exits non-zero if files would change |
| `--cpp-only` | — | Run `clang-format` only |
| `--python-only` | — | Run `isort` + `black` only |

Required tools (install once):

```bash
pip install black isort
# clang-format: ships with LLVM / VS Build Tools / Xcode CLT
```

---

## Windows

### Dependencies

| Tool | winget ID | Notes |
|---|---|---|
| Python 3.8+ | `Python.Python.3.12` | Runtime and pip |
| CMake 3.17+ | `Kitware.CMake` | Build system |
| VS Build Tools | `Microsoft.VisualStudio.2022.BuildTools` | MSVC C++17 compiler |

```powershell
winget install Python.Python.3.12
winget install Kitware.CMake
winget install Microsoft.VisualStudio.2022.BuildTools --override "--quiet --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended"
```

Then install the Python build dependencies:

```powershell
pip install scikit-build-core pybind11
```

### Quirks

- **DLL discovery**: Python 3.8+ automatically adds the extension module's directory to the DLL search path. The build system places all DLLs and `.pyd` files in the same `bin/` directory (`CMAKE_RUNTIME_OUTPUT_DIRECTORY`) so that Windows can find them without any `PATH` manipulation.
- **Shared CRT**: CMake sets `gtest_force_shared_crt=ON` to prevent GoogleTest from overriding the runtime library settings when building tests. Without this, MSVC will complain about mismatched CRT linkage.
- **Build config**: Always pass `--config Release` (or `Debug`) explicitly to `cmake --build` and `ctest` on Windows. MSVC is a multi-config generator and ignores `CMAKE_BUILD_TYPE`.

---

## Linux

### Dependencies

#### Debian/Ubuntu

```bash
sudo apt-get update
sudo apt-get install -y cmake g++ python3 python3-pip
pip install scikit-build-core pybind11
```

#### Fedora/RHEL

```bash
sudo dnf install -y cmake gcc-c++ python3 python3-pip
pip install scikit-build-core pybind11
```

### Quirks

- **RPATH**: Extension modules set `RPATH "$ORIGIN"` so that the pybind11 `.so` can find the sibling `libmyMathLib_*.so` at runtime without setting `LD_LIBRARY_PATH`.

---

## Linux → Windows Cross-Compile (MinGW)

Builds Windows `.exe` and `.dll` files on a Linux host and runs them under Wine. This does **not** build Python bindings — C++ tests only.

### Dependencies (Debian/Ubuntu)

```bash
sudo apt-get update
sudo apt-get install -y gcc-mingw-w64-x86-64 g++-mingw-w64-x86-64 wine64
```

### Build

```bash
# Locate the Wine binary (Ubuntu 24.04 ships it as 'wine', not 'wine64')
WINE_BIN=$(which wine64 2>/dev/null || which wine)

# Locate MinGW runtime DLLs so Wine can find them when running tests
MINGW_DLL_DIR=$(dirname $(x86_64-w64-mingw32-gcc -print-libgcc-file-name))
BUILD_BIN="$(pwd)/build-mingw/bin"
export WINEPATH="${MINGW_DLL_DIR};${BUILD_BIN}"   # semicolons, not colons

cmake -B build-mingw \
      -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/mingw-w64-x86_64.cmake \
      -DCMAKE_CROSSCOMPILING_EMULATOR="${WINE_BIN}" \
      -DBUILD_PYTHON_BINDINGS=OFF \
      -DBUILD_TESTING=ON \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_GTEST_DISCOVER_TESTS_DISCOVERY_MODE=PRE_TEST

cmake --build build-mingw --config Release
WINEDEBUG=-all ctest --test-dir build-mingw -C Release --output-on-failure
```

### Quirks

- **Wine binary name**: Ubuntu 24.04's `wine64` package installs the binary as `wine` (a universal 32/64-bit binary) rather than `wine64`. Use `which wine64 2>/dev/null || which wine` to locate it portably.
- **`WINEPATH` uses semicolons**: Wine's `WINEPATH` uses the Windows path separator (`;`), not the Unix colon. Setting it incorrectly causes Wine to silently fail to find MinGW runtime DLLs.
- **`WINEPATH` must include two directories**: the MinGW compiler runtime DLL directory (for `libgcc`, `libstdc++`, etc.) and the build `bin/` directory (for `libmyMathLib_*.dll`). Both are required for tests to run under Wine.
- **`WINEDEBUG=-all`**: Suppresses Wine's verbose debug output so that test results are readable.
- **`PRE_TEST` discovery mode**: `GTEST_DISCOVER_TESTS_DISCOVERY_MODE=PRE_TEST` is required for cross-compilation. The default `POST_BUILD` mode tries to run the test binary on the host during the build, which fails when the binary is a Windows `.exe`.
- **Python bindings not supported**: `BUILD_PYTHON_BINDINGS=OFF` is required. pybind11 needs the target Python interpreter headers and libraries, which are not available in the MinGW sysroot.

---

## macOS

### Dependencies

```bash
# Homebrew
brew install cmake python
pip install scikit-build-core pybind11
```

Xcode Command Line Tools are required for the C++ compiler:

```bash
xcode-select --install
```

### Quirks

- **RPATH**: Extension modules set `RPATH "@loader_path"` so that the pybind11 `.dylib` can find the sibling `libmyMathLib_*.dylib` at runtime without setting `DYLD_LIBRARY_PATH`.
- **Universal binaries**: The default build targets your host architecture. To build a fat `arm64+x86_64` binary, add `-DCMAKE_OSX_ARCHITECTURES="arm64;x86_64"` to the CMake configure step.

---

## CMake Options

| Option | Default | Description |
|---|---|---|
| `BUILD_PYTHON_BINDINGS` | `ON` | Build pybind11 Python extensions |
| `BUILD_TESTING` | `OFF` | Build C++ GoogleTest unit tests |
| `CMAKE_BUILD_TYPE` | _(none)_ | `Release` or `Debug`. Required for single-config generators (Makefile, Ninja). |
