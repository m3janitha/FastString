cmake_minimum_required (VERSION 3.16)

project(fixed_size_string VERSION 1.0)

set(CMAKE_CPP_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_VERBOSE_MAKEFILE ON)

if (MSVC)
    # add_compile_options(/W4 /WX)
    add_compile_options(/wd2220)
    set(CMAKE_CXX_FLAGS "-O3")
    #add_compile_definitions(FIXED_SIZE_STRING_DISABLE_IOSTREAM)
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

add_subdirectory(example)
add_subdirectory(benchmark)
add_subdirectory(test)
