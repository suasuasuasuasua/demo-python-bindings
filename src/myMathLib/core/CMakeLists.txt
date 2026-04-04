# ── C++ shared library ─────────────────────────────────────────────────────────
add_library(myMathLib_core SHARED
    math_ops.cpp
)

target_include_directories(myMathLib_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_definitions(myMathLib_core PRIVATE MYMATHLIB_EXPORTS)

target_compile_options(myMathLib_core PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>
)

# ── Python extension (_core) ───────────────────────────────────────────────────
if(BUILD_PYTHON_BINDINGS)
    pybind11_add_module(_core bindings.cpp)

    target_link_libraries(_core PRIVATE myMathLib_core)

    target_include_directories(_core PRIVATE include)

    if(APPLE)
        set_target_properties(_core PROPERTIES INSTALL_RPATH "@loader_path")
    elseif(UNIX)
        set_target_properties(_core PROPERTIES INSTALL_RPATH "$ORIGIN")
    endif()

    # Install extension and its C++ shared library into the Python package dir
    install(TARGETS _core        DESTINATION myMathLib)
    install(TARGETS myMathLib_core DESTINATION myMathLib)
endif()

# ── C++ tests ──────────────────────────────────────────────────────────────────
if(BUILD_TESTING)
    add_executable(test_math_ops
        ${PROJECT_SOURCE_DIR}/tests/cpp/test_math_ops.cpp
    )
    target_link_libraries(test_math_ops PRIVATE myMathLib_core GTest::gtest_main)
    target_include_directories(test_math_ops PRIVATE include)

    if(APPLE)
        set_target_properties(test_math_ops PROPERTIES BUILD_RPATH "@loader_path")
    elseif(UNIX)
        set_target_properties(test_math_ops PROPERTIES BUILD_RPATH "$ORIGIN")
    endif()

    gtest_discover_tests(test_math_ops)
endif()
