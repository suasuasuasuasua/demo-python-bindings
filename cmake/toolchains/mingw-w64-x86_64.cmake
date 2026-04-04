# Cross-compilation toolchain for targeting 64-bit Windows using MinGW-w64 on Linux.
#
# Usage:
#   cmake -B build-mingw \
#         -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/mingw-w64-x86_64.cmake \
#         -DBUILD_PYTHON_BINDINGS=OFF \
#         -DBUILD_TESTING=ON \
#         -DCMAKE_BUILD_TYPE=Release
#
# Prerequisites (Debian/Ubuntu):
#   sudo apt-get install gcc-mingw-w64-x86-64 g++-mingw-w64-x86-64 wine64
#
# The WINEPATH environment variable must include the MinGW runtime DLL directory
# and the build's bin/ directory so that Wine can find all shared libraries when
# running test executables:
#   export WINEPATH="$(dirname $(x86_64-w64-mingw32-gcc -print-libgcc-file-name)):$(pwd)/build-mingw/bin"

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR AMD64)

set(CMAKE_C_COMPILER   x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER  x86_64-w64-mingw32-windres)

# Use Wine to run Windows test binaries on the Linux host.
set(CMAKE_CROSSCOMPILING_EMULATOR wine64)

# Restrict CMake's find_* commands to the MinGW sysroot so that host
# libraries are not accidentally picked up.
set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
