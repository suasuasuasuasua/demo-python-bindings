# ── C++ shared library
# ─────────────────────────────────────────────────────────
add_library(myMathLib_numerics SHARED numerics.cpp)

target_include_directories(
  myMathLib_numerics
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>)

# Expose the operators (and its transitive constants) headers to consumers.
target_link_libraries(myMathLib_numerics PUBLIC myMathLib_operators)

target_compile_definitions(myMathLib_numerics PRIVATE NUMERICS_EXPORTS)

target_compile_options(
  myMathLib_numerics PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/W4>
                             $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>)

# At install time myMathLib_numerics lives in myMathLib/ alongside
# myMathLib_operators.so and myMathLib_constants.so, so $ORIGIN resolves both.
if(BUILD_PYTHON_BINDINGS)
  pybind11_add_module(_numerics bindings.cpp)

  target_link_libraries(_numerics PRIVATE myMathLib_numerics)

  target_include_directories(_numerics PRIVATE include)

  # _numerics is installed in myMathLib/numerics/ while myMathLib_numerics.so
  # (and its transitive deps operators, constants) live one level up in myMathLib/.
  if(APPLE)
    set_target_properties(_numerics PROPERTIES INSTALL_RPATH "@loader_path/..")
    set_target_properties(myMathLib_numerics PROPERTIES INSTALL_RPATH
                                                        "@loader_path")
  elseif(UNIX)
    set_target_properties(_numerics PROPERTIES INSTALL_RPATH "$ORIGIN/..")
    set_target_properties(myMathLib_numerics PROPERTIES INSTALL_RPATH "$ORIGIN")
  endif()

  install(TARGETS _numerics DESTINATION myMathLib/numerics)
  install(TARGETS myMathLib_numerics DESTINATION myMathLib)
endif()

# ── C++ tests
# ──────────────────────────────────────────────────────────────────
if(BUILD_TESTING)
  add_executable(test_numerics ${PROJECT_SOURCE_DIR}/tests/cpp/test_numerics.cpp)
  target_link_libraries(test_numerics PRIVATE myMathLib_numerics GTest::gtest_main)
  target_include_directories(test_numerics PRIVATE include)

  if(APPLE)
    set_target_properties(test_numerics PROPERTIES BUILD_RPATH "@loader_path")
  elseif(UNIX)
    set_target_properties(test_numerics PROPERTIES BUILD_RPATH "$ORIGIN")
  endif()

  gtest_discover_tests(test_numerics DISCOVERY_TIMEOUT 60)
endif()
