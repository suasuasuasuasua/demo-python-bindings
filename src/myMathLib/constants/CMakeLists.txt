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
  pybind11_add_module(_constants bindings.cpp)

  target_link_libraries(_constants PRIVATE myMathLib_constants)

  target_include_directories(_constants PRIVATE include)

  # _constants is installed in myMathLib/constants/ while myMathLib_constants.so
  # lives one level up in myMathLib/, so $ORIGIN/.. (or @loader_path/..) reaches it.
  if(APPLE)
    set_target_properties(_constants PROPERTIES INSTALL_RPATH "@loader_path/..")
  elseif(UNIX)
    set_target_properties(_constants PROPERTIES INSTALL_RPATH "$ORIGIN/..")
  endif()

  install(TARGETS _constants DESTINATION myMathLib/constants)
  install(TARGETS myMathLib_constants DESTINATION myMathLib)
endif()

# ── C++ tests
# ──────────────────────────────────────────────────────────────────
if(BUILD_TESTING)
  add_executable(test_constants ${PROJECT_SOURCE_DIR}/tests/cpp/test_constants.cpp)
  target_link_libraries(test_constants PRIVATE myMathLib_constants GTest::gtest_main)
  target_include_directories(test_constants PRIVATE include)

  if(APPLE)
    set_target_properties(test_constants PROPERTIES BUILD_RPATH "@loader_path")
  elseif(UNIX)
    set_target_properties(test_constants PROPERTIES BUILD_RPATH "$ORIGIN")
  endif()

  gtest_discover_tests(test_constants DISCOVERY_TIMEOUT 60)
endif()
