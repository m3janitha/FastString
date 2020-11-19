#include "include/fixed_size_str.h"

int main()
{
    /* define types */
    using string8 = fls::fixed_size_str<7>;
    using string64 = fls::fixed_size_str<63>;

    /* default construction */
    constexpr string8 a{};
    constexpr auto a_length = a.length();               // a_length is 0
    constexpr auto a_max_size = a.max_size();           // a_max_size is 7

    /* using with string view */
    constexpr string8 b("abcdefghij", 10);              // truncated. b is "abcdefg";
    constexpr auto b_sub_str = b.str().substr(0, 2);    // b_sub_str is "ab"
    constexpr auto b_length = b.length();               // b_length is 7

    /* comparison */
    constexpr string8 c("abcd");
    constexpr string8 d("abcd");
    constexpr string8 e("abcf");
    constexpr auto f = (c == d);        // true 
    constexpr auto g = (d == e);        // false

    /* append */
    string8 h("abc");
    h.append("d");                      // h is "abcd"
    h.append("efghi", 5);               // h is "abcdefg". rest is truncated

    /* reset */
    h.reset("1234");                    // h is "1234";
    auto h_length = h.length();         // h_length is 4

    /* clear */
    h.clear();                          // h is empty() "";

    /* reset */
    h.reset("abcd");                    // h is "abcd"
    h.reset("xyz", 3);                  // h is "xyz"

    /* use for member variables */
    struct test_struct
    {
        std::uint32_t a_{};
        std::uint64_t b_{};
        string8 c_{ "abcd" };           // uses only 8 + 4 bytes and created in stack

        constexpr auto get_c() const { return c_.str(); }
        constexpr void set_c(const char* str) { c_.reset(str); }
    };

    auto test_struct_size = sizeof(test_struct);
    constexpr test_struct t;
    constexpr auto t_a = t.get_c();
}