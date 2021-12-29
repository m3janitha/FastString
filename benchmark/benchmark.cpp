#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include "fixed_size_str.h"
#include <string>
#include <array>

TEST_CASE("construct") {
    BENCHMARK_ADVANCED("std::string from const char*")(Catch::Benchmark::Chronometer meter) {
        const char* str = "Hello World!";

        meter.measure([&str] {
            std::string a = str;
            return a.length();
        });
    };

    BENCHMARK_ADVANCED("std::string from constexpr const char*")(Catch::Benchmark::Chronometer meter) {
        constexpr const char* str = "Hello World!";

        meter.measure([&str] {
            std::string a (str);
            return a.length();
        });
    };

    BENCHMARK_ADVANCED("fixed_size_str from const char*")(Catch::Benchmark::Chronometer meter) {
        using string = fss::fixed_size_str<24>;
        const char* str = "Hello World!";

        meter.measure([&str] {
            string a = str;
            return a.length();
        });
    };

    BENCHMARK_ADVANCED("fixed_size_str from constexpr const char*")(Catch::Benchmark::Chronometer meter) {
        using string = fss::fixed_size_str<24>;
        constexpr const char* str = "Hello World!";

        meter.measure([&str] {
            constexpr string a = str;
            return a.length();
        });
    };


    BENCHMARK_ADVANCED("std::string from buffer")(Catch::Benchmark::Chronometer meter) {
        std::array<char, 24> buffer = {'H', 'e', 'l', 'l' , 'o' , ' ' , 'W', 'o', 'r', 'l', 'd', '!', '\0' };

        meter.measure([&buffer] {
            std::string a = buffer.data();
            return a.length();
        });
    };

    BENCHMARK_ADVANCED("fixed_size_str from buffer")(Catch::Benchmark::Chronometer meter) {
        using string = fss::fixed_size_str<24>;
        std::array<char, 24> buffer = { 'H', 'e', 'l', 'l' , 'o' , ' ' , 'W', 'o', 'r', 'l', 'd', '!', '\0' };

        meter.measure([&buffer] {
            string a = buffer.data();
            return a.length();
        });
    };

    BENCHMARK_ADVANCED("std::string from constexpr buffer")(Catch::Benchmark::Chronometer meter) {
        constexpr std::array<char, 24> buffer = { 'H', 'e', 'l', 'l' , 'o' , ' ' , 'W', 'o', 'r', 'l', 'd', '!', '\0' };

        meter.measure([&buffer] {
            std::string a = buffer.data();
            return a.length();
        });
    };

    BENCHMARK_ADVANCED("fixed_size_str from constexpr buffer")(Catch::Benchmark::Chronometer meter) {
        using string = fss::fixed_size_str<24>;
        constexpr std::array<char, 24> buffer = { 'H', 'e', 'l', 'l' , 'o' , ' ' , 'W', 'o', 'r', 'l', 'd', '!', '\0' };

        meter.measure([&buffer] {
            constexpr string a = buffer.data();
            return a.length();
        });
    };

    BENCHMARK_ADVANCED("fixed_size_str from buffer with size")(Catch::Benchmark::Chronometer meter) {
        using string = fss::fixed_size_str<24>;
        std::array<char, 24> buffer = { 'H', 'e', 'l', 'l' , 'o' , ' ' , 'W', 'o', 'r', 'l', 'd', '!', '\0' };
        size_t str_size = 12;

        string a_test(buffer.data(), str_size);
        REQUIRE(12 == a_test.length());

        meter.measure([&buffer, str_size] {
            string a (buffer.data(), str_size);
            return a.length();
        });
    };

    BENCHMARK_ADVANCED("fixed_size_str from constexpr buffer with size")(Catch::Benchmark::Chronometer meter) {
        using string = fss::fixed_size_str<24>;
        constexpr std::array<char, 24> buffer = { 'H', 'e', 'l', 'l' , 'o' , ' ' , 'W', 'o', 'r', 'l', 'd', '!', '\0' };
        constexpr size_t str_size = 12;

        constexpr string a_test(buffer.data(), str_size);
        REQUIRE(12 == a_test.length());

        meter.measure([&buffer, str_size] {
            string a(buffer.data(), str_size);
            return a.length();
        });
    };
}