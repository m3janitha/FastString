cmake_minimum_required (VERSION 3.12)

project(fixed_size_string LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_library(fixed_size_string INTERFACE)
add_library(fixed_size_string::fixed_size_string ALIAS fixed_size_string)
target_sources(fixed_size_string INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/fixed_size_str.h)
target_include_directories(fixed_size_string INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(libs/catch2)
option(ENABLE_TESTS "Enable Tests" ON)
if(ENABLE_TESTS)
enable_testing()
add_subdirectory(tests)
endif()

option(ENABLE_BENCHMARKS "Enable Benchmarks" OFF)
if(ENABLE_BENCHMARKS)
add_subdirectory(benchmark)
endif()

option(ENABLE_EXAMPLES "Enable Examples" OFF)
if(ENABLE_EXAMPLES)
add_subdirectory(examples)
endif()
