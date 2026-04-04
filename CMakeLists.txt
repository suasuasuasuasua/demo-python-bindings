cmake_minimum_required(VERSION 3.17)
project(myMathLib VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable position-independent code for shared libraries
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(BUILD_PYTHON_BINDINGS "Build the pybind11 Python extension" ON)
option(BUILD_TESTING "Build C++ tests" OFF)

# Place all runtime artifacts (DLLs, executables) in the same directory so
# that Windows can locate the shared library without PATH manipulation.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(BUILD_PYTHON_BINDINGS)
    find_package(pybind11 CONFIG REQUIRED)

    # Install the pure-Python package so that myMathLib/__init__.py is
    # included in the wheel alongside the extension modules.
    install(FILES src/myMathLib/python/__init__.py DESTINATION myMathLib)
endif()

if(BUILD_TESTING)
    include(CTest)
endif()

# ── Sub-libraries ──────────────────────────────────────────────────────────────
add_subdirectory(src/myMathLib/core)
add_subdirectory(src/myMathLib/linalg)
add_subdirectory(src/myMathLib/calculus)
