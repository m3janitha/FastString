cmake_minimum_required (VERSION 3.16)

project(fixed_size_string VERSION 1.0)

set(CMAKE_CPP_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_VERBOSE_MAKEFILE ON)

if (MSVC)
    # warning level 4 and all warnings as errors
    # add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    message("setting CMAKE_CXX_FLAGS")
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_CXX_FLAGS "-O3")
endif()

include(FetchContent)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(googletest)

# set(BENCHMARK_ENABLE_TESTING OFF)

# FetchContent_Declare(
# 	googlebenchmark
# 	GIT_REPOSITORY https://github.com/google/benchmark
# 	GIT_TAG v1.6.0
# )

add_subdirectory(example)
add_subdirectory(test)
