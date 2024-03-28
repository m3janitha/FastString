include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable (examples main.cpp)
# target_link_libraries(examples PRIVATE FastString)

if(MSVC)
  target_compile_options(examples PRIVATE /W4 /WX)
else()
  
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message("setting MSVC CMAKE_CXX_FLAGS")
    target_compile_options(examples PRIVATE /W4 /WX)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message("setting GCC CMAKE_CXX_FLAGS")
    target_compile_options(examples PRIVATE -Wall -Wextra -pedantic -Werror -Wno-unused-but-set-variable)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(examples PRIVATE -Wno-unused-variable)    
else()
    message("setting ${CMAKE_CXX_COMPILER_ID} CMAKE_CXX_FLAGS")
endif()