# ── C++ shared library ─────────────────────────────────────────────────────────
add_library(myMathLib_linalg SHARED
    linalg_ops.cpp
)

target_include_directories(myMathLib_linalg
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_definitions(myMathLib_linalg PRIVATE LINALG_EXPORTS)

target_compile_options(myMathLib_linalg PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>
)

# ── Python extension (linalg) ──────────────────────────────────────────────────
if(BUILD_PYTHON_BINDINGS)
    pybind11_add_module(linalg bindings.cpp)

    target_link_libraries(linalg PRIVATE myMathLib_linalg)

    target_include_directories(linalg PRIVATE include)

    if(APPLE)
        set_target_properties(linalg PROPERTIES INSTALL_RPATH "@loader_path")
    elseif(UNIX)
        set_target_properties(linalg PROPERTIES INSTALL_RPATH "$ORIGIN")
    endif()

    # Install extension and its C++ shared library into the Python package dir
    install(TARGETS linalg           DESTINATION myMathLib)
    install(TARGETS myMathLib_linalg DESTINATION myMathLib)
endif()

# ── C++ tests ──────────────────────────────────────────────────────────────────
if(BUILD_TESTING)
    add_executable(test_linalg
        ${PROJECT_SOURCE_DIR}/tests/cpp/test_linalg.cpp
    )
    target_link_libraries(test_linalg PRIVATE myMathLib_linalg)
    target_include_directories(test_linalg PRIVATE include)

    if(APPLE)
        set_target_properties(test_linalg PROPERTIES BUILD_RPATH "@loader_path")
    elseif(UNIX)
        set_target_properties(test_linalg PROPERTIES BUILD_RPATH "$ORIGIN")
    endif()

    add_test(NAME linalg COMMAND test_linalg)
endif()
