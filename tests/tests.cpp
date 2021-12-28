#include <catch2/catch_test_macros.hpp>
#include "fixed_size_str.h"
#include <iostream>
#include <string>
#include <array>

using namespace std::string_literals;

/* define types */
using string8 = fss::fixed_size_str<7>;
using string64 = fss::fixed_size_str<63>;

struct test_struct
{
    std::uint32_t a_{};
    std::uint64_t b_{};
    string8 c_ = "abcd";                           

    constexpr auto get_c() const noexcept { return c_.c_str(); }
    constexpr auto get_c_str() const noexcept { return c_.str(); }
    constexpr void set_c(const char* str) { c_.reset(str); }
};

TEST_CASE("default construction") {
    constexpr string8 a{};

    REQUIRE(0 == a.length());
    REQUIRE(a.empty());
    REQUIRE(7 == a.max_size());
}

TEST_CASE("construction from constexpr") {
    constexpr const char* str = "1234";
    constexpr string8 a = str;

    REQUIRE(4 == a.length());
    REQUIRE_FALSE(a.empty());
    REQUIRE(7 == a.max_size());
}

TEST_CASE("construction from const buffer") {
    using string24 = fss::fixed_size_str<23>;
    constexpr std::array<char, 24> buffer = { 'H', 'e', 'l', 'l' , 'o' , ' ' , 'W', 'o', 'r', 'l', 'd', '!', '\0' };
    constexpr size_t buffer_str_size = 12;

    constexpr string24 a(buffer.data(), buffer_str_size);

    REQUIRE("Hello World!"s == a.c_str());
    REQUIRE(12 == a.length());
    REQUIRE_FALSE(a.empty());
    REQUIRE(23 == a.max_size());
}

TEST_CASE("construction from buffer") {
    using string24 = fss::fixed_size_str<23>;
    std::array<char, 24> buffer = { 'H', 'e', 'l', 'l' , 'o' , ' ' , 'W', 'o', 'r', 'l', 'd', '!', '\0' };
    size_t buffer_str_size = 12;

    string24 a (buffer.data(), buffer_str_size);

    REQUIRE("Hello World!"s == a.c_str());
    REQUIRE(12 == a.length());
    REQUIRE_FALSE(a.empty());
    REQUIRE(23 == a.max_size());
}

TEST_CASE("copy construction") {
    constexpr string8 a{};
    constexpr auto a_copy_c = a;
    auto a_copy = a;
    auto a_move = std::move(a_copy);

    REQUIRE(a_copy.length() == a.length());
    REQUIRE(a.empty());
    REQUIRE(a_copy.empty());
    REQUIRE(a_copy.max_size() == a.max_size());
}

TEST_CASE("move construction") {
    constexpr string8 a{};
    auto a_copy = a;
    auto a_move = std::move(a_copy);

    REQUIRE(a_move.length() == a.length());
    REQUIRE(a.empty());
    REQUIRE(a_move.empty());
    REQUIRE(a_move.max_size() == a.max_size());
}

TEST_CASE("copy assignment") {
    constexpr string8 b{ "1234", 4 };                   
    string8 c{ "lmnopqrstuvxyz" };   
    REQUIRE("1234"s == b.c_str());
    REQUIRE("lmnopqr"s == c.c_str());   // c is "lmnopqr"

    c = b;
        
    REQUIRE("1234"s == c.c_str());
}

TEST_CASE("move assignment") {
    constexpr string8 b{ "1234", 4 };
    string8 c{ "lmnopqrstuvxyz" };
    string8 d{ "56789" };
    c = std::move(d);

    REQUIRE("56789"s == c.c_str());                     
}

TEST_CASE("using with string view") {
    constexpr string8 e{ "abcdefghij", 10 };            
    constexpr auto e_sub_str = e.str().substr(0, 2);
    constexpr auto e_str = e.str();
    constexpr auto e_length = e.length();              

    REQUIRE("abcdefg"s == e.c_str());                   // truncated. e is "abcdefg";
    REQUIRE("ab"s == e_sub_str);
    REQUIRE("abcdefg"s == e_str);
    REQUIRE(7 == e.length());
}

TEST_CASE("comparison") {
    constexpr string8 f{ "abcd" };
    constexpr string8 g{ "abcd" };
    constexpr string8 h{ "abcf" };

    REQUIRE((f == g));
    REQUIRE_FALSE((g == h));
}

TEST_CASE("append") {
    string8 k{ "abc" };                                 // k is "abc"
    REQUIRE("abc"s == k.c_str());              

    k.append("d");                                   
    REQUIRE("abcd"s == k.c_str());

    k.append("efghi", 5);                                             
    REQUIRE("abcdefg"s == k.c_str());                      // k is "abcdefg". rest is truncated   
}

TEST_CASE("clear") {
    string8 k{ "abcdefg" };                                 
    REQUIRE("abcdefg"s == k.c_str());
    REQUIRE_FALSE(k.empty());

    k.clear();
    REQUIRE(""s == k.c_str());
    REQUIRE(k.empty());
}

TEST_CASE("reset") {
    string8 k{ "abcdefg" };
    REQUIRE("abcdefg"s == k.c_str());
    REQUIRE(7 == k.length());

    k.reset("1234");                                                     
    REQUIRE("1234"s == k.c_str());
    REQUIRE(4 == k.length());

    k.reset("xyz", 3);                                                   
    REQUIRE("xyz"s == k.c_str());
    REQUIRE(3 == k.length());
}


TEST_CASE("remove_suffix") {
    string8 l{ "1234567" };
    REQUIRE("1234567"s == l.c_str());

    l.remove_suffix(3);                                                                   
    REQUIRE("1234"s == l.c_str());
}

TEST_CASE("remove_prefix") {
    string8 l{ "1234" };
    REQUIRE("1234"s == l.c_str());

    l.remove_prefix(2);
    REQUIRE("34"s == l.c_str());
}

TEST_CASE("stream operator") {
    string8 l{ "1234" };
    std::cout << l << std::endl;
}

TEST_CASE("using member variables") {
    constexpr auto test_struct_size = sizeof(test_struct);
    // uses only 8 + 4 bytes in stack
    REQUIRE(32 == test_struct_size);

    constexpr test_struct t{};
    constexpr auto t_c = t.get_c();
    constexpr auto t_c_str = t.get_c_str();

    REQUIRE("abcd"s == t_c);
    REQUIRE("abcd"s == t_c_str);


    test_struct t2{};
    t2.set_c("123456");
    const auto test_struct_size_2 = sizeof(t2);
    const auto t2_c = t2.get_c();
    const auto t2_c_str = t2.get_c();
    REQUIRE(32 == test_struct_size_2);

    REQUIRE("123456"s == t2_c);
    REQUIRE("123456"s == t2_c_str);
}

TEST_CASE("swap") {
    string8 k{ "xyz" };
    string8 l{ "34" };

    l.swap(k);                                          
    // l is "xyz" and k is "34"
    REQUIRE("xyz"s == l.c_str());
    REQUIRE("34"s == k.c_str());

    std::swap(l, k);                                         
    // l is "34" and k is "xyz"
    REQUIRE("34"s == l.c_str());
    REQUIRE("xyz"s == k.c_str());
}