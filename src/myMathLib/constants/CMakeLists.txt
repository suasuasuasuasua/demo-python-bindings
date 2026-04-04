# ── C++ shared library
# ─────────────────────────────────────────────────────────
add_library(myMathLib_constants SHARED constants.cpp)

target_include_directories(
  myMathLib_constants
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>)

target_compile_definitions(myMathLib_constants PRIVATE CONSTANTS_EXPORTS)

target_compile_options(
  myMathLib_constants PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/W4>
                              $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>)

# myMathLib_constants has no shared-library dependencies of its own, so no
# INSTALL_RPATH is needed.  It is installed at the myMathLib/ top level so that
# the dependent operators and numerics libraries (also in myMathLib/) can locate
# it with their own $ORIGIN RPATH.
if(BUILD_PYTHON_BINDINGS)
  install(TARGETS myMathLib_constants DESTINATION myMathLib)
endif()
