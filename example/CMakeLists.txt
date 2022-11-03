include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable (examples main.cpp)
# target_link_libraries(examples PRIVATE fixed_size_string)

if(MSVC)
  target_compile_options(examples PRIVATE /W4 /WX)
else()
  target_compile_options(examples PRIVATE -Wall -Wextra -pedantic -Werror)
endif()