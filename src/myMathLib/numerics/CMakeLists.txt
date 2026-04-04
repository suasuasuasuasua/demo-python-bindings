# ── C++ shared library ─────────────────────────────────────────────────────────
add_library(myMathLib_numerics SHARED
    numerics.cpp
)

target_include_directories(myMathLib_numerics
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Expose the operators (and its transitive constants) headers to consumers.
target_link_libraries(myMathLib_numerics PUBLIC myMathLib_operators)

target_compile_definitions(myMathLib_numerics PRIVATE NUMERICS_EXPORTS)

target_compile_options(myMathLib_numerics PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>
)

# At install time myMathLib_numerics lives in myMathLib/ alongside
# myMathLib_operators.so and myMathLib_constants.so, so $ORIGIN resolves both.
if(BUILD_PYTHON_BINDINGS)
    if(APPLE)
        set_target_properties(myMathLib_numerics PROPERTIES
            INSTALL_RPATH "@loader_path")
    elseif(UNIX)
        set_target_properties(myMathLib_numerics PROPERTIES
            INSTALL_RPATH "$ORIGIN")
    endif()

    install(TARGETS myMathLib_numerics DESTINATION myMathLib)
endif()
