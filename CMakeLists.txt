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

# ── C++ shared library ─────────────────────────────────────────────────────────
add_library(myMathLib_core SHARED
    src/myMathLib/math_ops.cpp
)

target_include_directories(myMathLib_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/myMathLib/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_definitions(myMathLib_core PRIVATE MYMATHLIB_EXPORTS)

target_compile_options(myMathLib_core PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>
)

# ── Python extension (pybind11) ────────────────────────────────────────────────
if(BUILD_PYTHON_BINDINGS)
    find_package(pybind11 CONFIG REQUIRED)

    pybind11_add_module(myMathLib
        src/myMathLib/bindings.cpp
    )

    target_link_libraries(myMathLib PRIVATE myMathLib_core)

    target_include_directories(myMathLib PRIVATE
        src/myMathLib/include
    )

    # Set RPATH so the extension can find the shared library at runtime
    if(APPLE)
        set_target_properties(myMathLib PROPERTIES
            INSTALL_RPATH "@loader_path"
        )
    elseif(UNIX)
        set_target_properties(myMathLib PROPERTIES
            INSTALL_RPATH "$ORIGIN"
        )
    endif()

    install(TARGETS myMathLib DESTINATION .)
    install(TARGETS myMathLib_core DESTINATION .)
endif()

# ── C++ tests (Catch2) ────────────────────────────────────────────────────────
if(BUILD_TESTING)
    include(CTest)
    include(FetchContent)

    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0
    )
    FetchContent_MakeAvailable(Catch2)

    add_executable(test_math_ops tests/cpp/test_math_ops.cpp)
    target_link_libraries(test_math_ops PRIVATE myMathLib_core Catch2::Catch2WithMain)
    target_include_directories(test_math_ops PRIVATE src/myMathLib/include)

    # On Linux/macOS set RPATH so the test executable finds the shared library
    if(APPLE)
        set_target_properties(test_math_ops PROPERTIES
            BUILD_RPATH "@loader_path"
        )
    elseif(UNIX)
        set_target_properties(test_math_ops PROPERTIES
            BUILD_RPATH "$ORIGIN"
        )
    endif()

    include(Catch)
    catch_discover_tests(test_math_ops)
endif()
