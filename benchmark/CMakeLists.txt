add_executable(fixed-size-string-benchmark benchmark.cpp)
target_link_libraries(fixed-size-string-benchmark PRIVATE fixed_size_string)
target_link_libraries(fixed-size-string-benchmark PRIVATE Catch2::Catch2WithMain)