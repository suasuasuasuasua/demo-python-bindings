# ── C++ shared library ─────────────────────────────────────────────────────────
add_library(myMathLib_calculus SHARED
    calculus_ops.cpp
)

target_include_directories(myMathLib_calculus
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_definitions(myMathLib_calculus PRIVATE CALCULUS_EXPORTS)

target_compile_options(myMathLib_calculus PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>
)

# ── Python extension (calculus) ────────────────────────────────────────────────
if(BUILD_PYTHON_BINDINGS)
    pybind11_add_module(calculus bindings.cpp)

    target_link_libraries(calculus PRIVATE myMathLib_calculus)

    target_include_directories(calculus PRIVATE include)

    if(APPLE)
        set_target_properties(calculus PROPERTIES INSTALL_RPATH "@loader_path")
    elseif(UNIX)
        set_target_properties(calculus PROPERTIES INSTALL_RPATH "$ORIGIN")
    endif()

    # Install extension and its C++ shared library into the Python package dir
    install(TARGETS calculus             DESTINATION myMathLib)
    install(TARGETS myMathLib_calculus   DESTINATION myMathLib)
endif()

# ── C++ tests ──────────────────────────────────────────────────────────────────
if(BUILD_TESTING)
    add_executable(test_calculus
        ${PROJECT_SOURCE_DIR}/tests/cpp/test_calculus.cpp
    )
    target_link_libraries(test_calculus PRIVATE myMathLib_calculus)
    target_include_directories(test_calculus PRIVATE include)

    if(APPLE)
        set_target_properties(test_calculus PROPERTIES BUILD_RPATH "@loader_path")
    elseif(UNIX)
        set_target_properties(test_calculus PROPERTIES BUILD_RPATH "$ORIGIN")
    endif()

    add_test(NAME calculus COMMAND test_calculus)
endif()
