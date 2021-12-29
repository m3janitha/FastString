add_executable(fixed-size-string-tests tests.cpp)
target_link_libraries(fixed-size-string-tests PRIVATE fixed_size_string)
target_link_libraries(fixed-size-string-tests PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/libs/catch2/extras)
include(CTest)
include(Catch)

# TODO: add catch_discover_tests
#catch_discover_tests(
#  fixed-size-string-tests
#  TEST_PREFIX
#  "unittests."
#  REPORTER
#  xml
#  OUTPUT_DIR
#  .
#  OUTPUT_PREFIX
#  "unittests."
#  OUTPUT_SUFFIX
#  .xml)

#option(ENABLE_COVERAGE "Enable Code Coverage in Tests" OFF)
#if(ENABLE_COVERAGE)
#  target_compile_options(fixed-size-string-tests PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
#  target_link_options(fixed-size-string-tests PUBLIC -fprofile-arcs -ftest-coverage)
#
#  setup_target_for_coverage_gcovr_html(
#    NAME
#    fixed-size-string-coverage-tests
#    EXECUTABLE
#    fixed-size-string-tests
#    EXCLUDE
#    "${PROJECT_SOURCE_DIR}/benchmark"
#    "${PROJECT_SOURCE_DIR}/tests"
#    "${PROJECT_SOURCE_DIR}/libs"
#    "${CMAKE_BINARY_DIR}/_deps")
#endif()
