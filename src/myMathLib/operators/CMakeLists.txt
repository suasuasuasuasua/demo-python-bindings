# ── C++ shared library ─────────────────────────────────────────────────────────
add_library(myMathLib_operators SHARED
    operators.cpp
)

target_include_directories(myMathLib_operators
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Expose the constants headers (and link the constants DLL) to consumers.
target_link_libraries(myMathLib_operators PUBLIC myMathLib_constants)

target_compile_definitions(myMathLib_operators PRIVATE OPERATORS_EXPORTS)

target_compile_options(myMathLib_operators PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>
)

# At install time myMathLib_operators lives in myMathLib/ alongside
# myMathLib_constants.so, so $ORIGIN (or @loader_path on Apple) is enough to
# resolve the constants dependency.
if(BUILD_PYTHON_BINDINGS)
    if(APPLE)
        set_target_properties(myMathLib_operators PROPERTIES
            INSTALL_RPATH "@loader_path")
    elseif(UNIX)
        set_target_properties(myMathLib_operators PROPERTIES
            INSTALL_RPATH "$ORIGIN")
    endif()

    install(TARGETS myMathLib_operators DESTINATION myMathLib)
endif()
