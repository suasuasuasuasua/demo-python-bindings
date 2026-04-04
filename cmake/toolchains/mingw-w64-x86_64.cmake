# Cross-compilation toolchain for targeting 64-bit Windows using MinGW-w64 on Linux.
#
# Usage:
#   WINE=$(which wine64)
#   MINGW_DLL=$(dirname $(x86_64-w64-mingw32-gcc -print-libgcc-file-name))
#   export WINEPATH="${MINGW_DLL};$(pwd)/build-mingw/bin"   # semicolons!
#   cmake -B build-mingw \
#         -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/mingw-w64-x86_64.cmake \
#         -DCMAKE_CROSSCOMPILING_EMULATOR="$WINE" \
#         -DBUILD_PYTHON_BINDINGS=OFF \
#         -DBUILD_TESTING=ON \
#         -DCMAKE_BUILD_TYPE=Release \
#         -DCMAKE_GTEST_DISCOVER_TESTS_DISCOVERY_MODE=PRE_TEST
#
# Prerequisites (Debian/Ubuntu):
#   sudo apt-get install gcc-mingw-w64-x86-64 g++-mingw-w64-x86-64 wine64
#
# Note: initialise the Wine prefix before running tests:
#   WINEDEBUG=-all wine64 wineboot --init

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR AMD64)

set(CMAKE_C_COMPILER   x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER  x86_64-w64-mingw32-windres)

# Use Wine to run Windows test binaries on the Linux host.
# Declared as a CACHE variable (without FORCE) so the caller can override it
# via -DCMAKE_CROSSCOMPILING_EMULATOR=/full/path/to/wine64.
set(CMAKE_CROSSCOMPILING_EMULATOR "wine64"
    CACHE STRING "Emulator used to run cross-compiled Windows test binaries")

# Restrict CMake's find_* commands to the MinGW sysroot so that host
# libraries are not accidentally picked up.
set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
