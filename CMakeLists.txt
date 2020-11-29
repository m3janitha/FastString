cmake_minimum_required (VERSION 2.6)

project(fixed_size_string)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include_directories ("include")

add_executable (examples
	examples/main.cpp)