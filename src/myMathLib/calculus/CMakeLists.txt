# ── C++ shared library ─────────────────────────────────────────────────────────
add_library(myMathLib_calculus SHARED
    calculus_ops.cpp
)

target_include_directories(myMathLib_calculus
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Pull in numerics (which transitively exposes operators → constants).
target_link_libraries(myMathLib_calculus PUBLIC myMathLib_numerics)

target_compile_definitions(myMathLib_calculus PRIVATE CALCULUS_EXPORTS)

target_compile_options(myMathLib_calculus PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>
)

# ── Python extension (calculus) ────────────────────────────────────────────────
if(BUILD_PYTHON_BINDINGS)
    pybind11_add_module(_calculus bindings.cpp)

    target_link_libraries(_calculus PRIVATE myMathLib_calculus)

    target_include_directories(_calculus PRIVATE include)

    # _calculus and myMathLib_calculus are installed together in myMathLib/calculus/.
    # _calculus needs $ORIGIN to locate myMathLib_calculus.so in the same directory.
    # myMathLib_calculus needs both $ORIGIN (for any peer libs in the same dir) and
    # $ORIGIN/.. to reach the utility DLLs (numerics, operators, constants) one
    # level up in myMathLib/.
    if(APPLE)
        set_target_properties(_calculus PROPERTIES
            INSTALL_RPATH "@loader_path")
        set_target_properties(myMathLib_calculus PROPERTIES
            INSTALL_RPATH "@loader_path:@loader_path/../")
    elseif(UNIX)
        set_target_properties(_calculus PROPERTIES
            INSTALL_RPATH "$ORIGIN")
        set_target_properties(myMathLib_calculus PROPERTIES
            INSTALL_RPATH "$ORIGIN:$ORIGIN/..")
    endif()

    # Install extension and its C++ shared library into the calculus sub-package dir
    install(TARGETS _calculus            DESTINATION myMathLib/calculus)
    install(TARGETS myMathLib_calculus   DESTINATION myMathLib/calculus)
endif()

# ── C++ tests ──────────────────────────────────────────────────────────────────
if(BUILD_TESTING)
    add_executable(test_calculus
        ${PROJECT_SOURCE_DIR}/tests/cpp/test_calculus.cpp
    )
    target_link_libraries(test_calculus PRIVATE myMathLib_calculus GTest::gtest_main)
    target_include_directories(test_calculus PRIVATE include)

    if(APPLE)
        set_target_properties(test_calculus PROPERTIES BUILD_RPATH "@loader_path")
    elseif(UNIX)
        set_target_properties(test_calculus PROPERTIES BUILD_RPATH "$ORIGIN")
    endif()

    gtest_discover_tests(test_calculus)
endif()
