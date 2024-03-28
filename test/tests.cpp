#include <FastString.h>
#include <array>

#include <gtest/gtest.h>

using namespace std::string_literals;

/* define types */
using string8 = fss::fixed_size_str<7>;
using string64 = fss::fixed_size_str<63>;

TEST(TestFixture, default_construction)
{
    constexpr string8 a{};

    ASSERT_EQ(0, a.length());
    ASSERT_TRUE(a.empty());
    ASSERT_EQ(7, a.max_size());
}

TEST(TestFixture, construction_from_constexpr)
{
    constexpr const char *str = "1234";
    constexpr string8 a = str;

    ASSERT_EQ(4, a.length());
    ASSERT_FALSE(a.empty());
    ASSERT_EQ(7, a.max_size());
}

TEST(TestFixture, construction_from_const_buffer)
{
    using string24 = fss::fixed_size_str<23>;
    constexpr std::array<char, 24> buffer{'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\0'};
    constexpr size_t buffer_str_size = 12;

    constexpr string24 a(buffer.data(), buffer_str_size);

    ASSERT_EQ("Hello World!"s, a.c_str());
    ASSERT_EQ(12, a.length());
    ASSERT_FALSE(a.empty());
    ASSERT_EQ(23, a.max_size());
}

TEST(TestFixture, construction_from_buffer)
{
    using string24 = fss::fixed_size_str<23>;
    std::array<char, 24> buffer = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\0'};
    size_t buffer_str_size = 12;

    string24 a(buffer.data(), buffer_str_size);

    ASSERT_EQ("Hello World!"s, a.c_str());
    ASSERT_EQ(12, a.length());
    ASSERT_FALSE(a.empty());
    ASSERT_EQ(23, a.max_size());
}

TEST(TestFixture, copy_construction)
{
    constexpr string8 a{"abc"};
    auto a_copy = a;

    ASSERT_EQ(a_copy.length(), a.length());
    ASSERT_FALSE(a.empty());
    ASSERT_FALSE(a_copy.empty());
    ASSERT_EQ(a_copy.max_size(), a.max_size());
}

TEST(TestFixture, move_construction)
{
    constexpr string8 a{"abc"};
    auto a_copy = a;
    auto a_move = std::move(a_copy);

    ASSERT_EQ(a_move.length(), a.length());
    ASSERT_FALSE(a.empty());
    ASSERT_FALSE(a_move.empty());
    ASSERT_EQ(a_move.max_size(), a.max_size());
}

TEST(TestFixture, copy_assignment)
{
    constexpr string8 b{"1234", 4};
    string8 c{"lmnopqrstuvxyz"};

    ASSERT_EQ("1234"s, b.c_str());
    ASSERT_EQ("lmnopqr"s, c.c_str()); // c is "lmnopqr"

    c = b;

    ASSERT_EQ("1234"s, c.c_str());
}

TEST(TestFixture, move_assignment)
{
    constexpr string8 a{"1234", 4};
    string8 b{"lmnopqrstuvxyz"};
    b = std::move(a);

    ASSERT_EQ("1234"s, b.c_str());
}

TEST(TestFixture, using_with_string_view)
{
    constexpr string8 e{"abcdefghij", 10};
    //constexpr auto e_sub_str = e.str().substr(0, 2);
    //constexpr auto e_str = e.str();
    auto e_sub_str = e.str().substr(0, 2);
    auto e_str = e.str();
    constexpr auto e_length = e.length();

    ASSERT_EQ("abcdefg"s, e.c_str()); // truncated. e is "abcdefg";
    ASSERT_EQ("ab"s, e_sub_str);
    ASSERT_EQ("abcdefg"s, e_str);
    ASSERT_EQ(7, e.length());
}

TEST(TestFixture, comparison)
{
    constexpr string8 f{"abcd"};
    constexpr string8 g{"abcd"};
    constexpr string8 h{"abcf"};

    ASSERT_TRUE((f == g));
    ASSERT_FALSE((g == h));
}

TEST(TestFixture, append)
{
    string8 k{"abc"}; // k is "abc"
    ASSERT_EQ("abc"s, k.c_str());

    k.append("d");
    ASSERT_EQ("abcd"s, k.c_str());

    k.append("efghi", 5);
    ASSERT_EQ("abcdefg"s, k.c_str()); // k is "abcdefg". rest is truncated
}

TEST(TestFixture, clear)
{
    string8 k{"abcdefg"};
    ASSERT_EQ("abcdefg"s, k.c_str());
    ASSERT_FALSE(k.empty());

    k.clear();
    ASSERT_EQ(""s, k.c_str());
    ASSERT_TRUE(k.empty());
}

TEST(TestFixture, reset) 
{
    string8 k{ "abcdefg" };
    ASSERT_EQ("abcdefg"s, k.c_str());
    ASSERT_EQ(7, k.length());

    k.reset("1234");
    ASSERT_EQ("1234"s, k.c_str());
    ASSERT_EQ(4, k.length());

    k.reset("xyz", 3);
    ASSERT_EQ("xyz"s, k.c_str());
    ASSERT_EQ(3, k.length());
}

TEST(TestFixture, remove_suffix)
 {
    string8 l{ "1234567" };
    ASSERT_EQ("1234567"s, l.c_str());

    l.remove_suffix(3);
    ASSERT_EQ("1234"s, l.c_str());
}

TEST(TestFixture, remove_prefix) 
{
    string8 l{ "1234" };
    ASSERT_EQ("1234"s, l.c_str());

    l.remove_prefix(2);
    ASSERT_EQ("34"s, l.c_str());
}

TEST(TestFixture, stream_operator) 
{
    string8 l{ "1234" };
    std::cout << l << std::endl;
    ASSERT_TRUE(1);
}

TEST(TestFixture, swap) 
{
    string8 k{ "xyz" };
    string8 l{ "34" };

    l.swap(k);
    // l is "xyz" and k is "34"
    ASSERT_EQ("xyz"s, l.c_str());
    ASSERT_EQ("34"s, k.c_str());

    std::swap(l, k);
    // l is "34" and k is "xyz"
    ASSERT_EQ("34"s, l.c_str());
    ASSERT_EQ("xyz"s, k.c_str());
}

struct test_struct
{
    std::uint32_t a_{};
    std::uint64_t b_{};
    string8 c_ = "abcd";                           

    constexpr auto get_c() const noexcept { return c_.c_str(); }
    constexpr auto get_c_str() const noexcept { return c_.str(); }
    constexpr void set_c(const char* str) { c_.reset(str); }
};

TEST(TestFixture, using_member_variables) 
{
    constexpr auto test_struct_size = sizeof(test_struct);
    // uses only 8 + 4 bytes in stack
    ASSERT_EQ(32, sizeof(test_struct));

    constexpr test_struct t{};
    // constexpr auto t_c = t.get_c();
    // constexpr auto t_c_str = t.get_c_str();
    auto t_c = t.get_c();
    auto t_c_str = t.get_c_str();

    ASSERT_EQ("abcd"s, t_c);
    ASSERT_EQ("abcd"s, t_c_str);

    test_struct t2{};
    t2.set_c("123456");
    const auto t2_c = t2.get_c();
    const auto t2_c_str = t2.get_c();
    ASSERT_EQ(32, sizeof(t2));

    ASSERT_EQ("123456"s, t2_c);
    ASSERT_EQ("123456"s, t2_c_str);
}
