include_directories(${PROJECT_SOURCE_DIR}/include)

set(BENCHMARK_ENABLE_TESTING OFF)

FetchContent_Declare(
	googlebenchmark
	GIT_REPOSITORY https://github.com/google/benchmark
	GIT_TAG v1.6.0
)

FetchContent_MakeAvailable(googlebenchmark)

add_executable(benchmark_test benchmark_test.cpp)
target_link_libraries(benchmark_test benchmark::benchmark)
target_link_libraries(benchmark_test GTest::gtest GTest::gtest_main)


