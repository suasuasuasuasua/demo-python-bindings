cmake_minimum_required(VERSION 3.17)
project(
  myMathLib
  VERSION 0.1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable position-independent code for shared libraries
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(BUILD_PYTHON_BINDINGS "Build the pybind11 Python extension" ON)
option(BUILD_TESTING "Build C++ tests" OFF)

# Place all runtime artifacts (DLLs, executables) in the same directory so that
# Windows can locate the shared library without PATH manipulation.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(BUILD_PYTHON_BINDINGS)
  find_package(pybind11 CONFIG REQUIRED)
endif()

if(BUILD_TESTING)
  include(CTest)

  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP ON)
  # Prevent GoogleTest from overriding the compiler/linker settings on Windows
  set(gtest_force_shared_crt
      ON
      CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  include(GoogleTest)
endif()

# ── Sub-libraries
# ────────────────────────────────────────────────────────────── Shared utility
# libraries (order matters: each depends on the ones above it).
add_subdirectory(src/myMathLib/constants)
add_subdirectory(src/myMathLib/operators)
add_subdirectory(src/myMathLib/numerics)

add_subdirectory(src/myMathLib/core)
add_subdirectory(src/myMathLib/linalg)
add_subdirectory(src/myMathLib/calculus)
