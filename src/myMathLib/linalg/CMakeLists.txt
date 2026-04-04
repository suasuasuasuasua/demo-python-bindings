# ── C++ shared library ─────────────────────────────────────────────────────────
add_library(myMathLib_linalg SHARED
    linalg_ops.cpp
)

target_include_directories(myMathLib_linalg
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Pull in numerics (which transitively exposes operators → constants).
target_link_libraries(myMathLib_linalg PUBLIC myMathLib_numerics)

target_compile_definitions(myMathLib_linalg PRIVATE LINALG_EXPORTS)

target_compile_options(myMathLib_linalg PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>
)

# ── Python extension (linalg) ──────────────────────────────────────────────────
if(BUILD_PYTHON_BINDINGS)
    pybind11_add_module(_linalg bindings.cpp)

    target_link_libraries(_linalg PRIVATE myMathLib_linalg)

    target_include_directories(_linalg PRIVATE include)

    # _linalg and myMathLib_linalg are installed together in myMathLib/linalg/.
    # _linalg needs $ORIGIN to locate myMathLib_linalg.so in the same directory.
    # myMathLib_linalg needs both $ORIGIN (for any peer libs in the same dir) and
    # $ORIGIN/.. to reach the utility DLLs (numerics, operators, constants) one
    # level up in myMathLib/.
    if(APPLE)
        set_target_properties(_linalg PROPERTIES
            INSTALL_RPATH "@loader_path")
        set_target_properties(myMathLib_linalg PROPERTIES
            INSTALL_RPATH "@loader_path:@loader_path/../")
    elseif(UNIX)
        set_target_properties(_linalg PROPERTIES
            INSTALL_RPATH "$ORIGIN")
        set_target_properties(myMathLib_linalg PROPERTIES
            INSTALL_RPATH "$ORIGIN:$ORIGIN/..")
    endif()

    # Install extension and its C++ shared library into the linalg sub-package dir
    install(TARGETS _linalg          DESTINATION myMathLib/linalg)
    install(TARGETS myMathLib_linalg DESTINATION myMathLib/linalg)
endif()

# ── C++ tests ──────────────────────────────────────────────────────────────────
if(BUILD_TESTING)
    add_executable(test_linalg
        ${PROJECT_SOURCE_DIR}/tests/cpp/test_linalg.cpp
    )
    target_link_libraries(test_linalg PRIVATE myMathLib_linalg GTest::gtest_main)
    target_include_directories(test_linalg PRIVATE include)

    if(APPLE)
        set_target_properties(test_linalg PROPERTIES BUILD_RPATH "@loader_path")
    elseif(UNIX)
        set_target_properties(test_linalg PROPERTIES BUILD_RPATH "$ORIGIN")
    endif()

    gtest_discover_tests(test_linalg DISCOVERY_TIMEOUT 60)
endif()
