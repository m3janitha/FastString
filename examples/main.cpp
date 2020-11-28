#include <iostream>
#include <fixed_size_str.h>

int main()
{
    /* define types */
    using string8 = fss::fixed_size_str<7>;
    using string64 = fss::fixed_size_str<63>;

    /* default construction */
    constexpr string8 a{};
    constexpr auto a_length = a.length();               // a_length is 0
    constexpr auto a_empty = a.empty();                 // a_empty is true
    constexpr auto a_max_size = a.max_size();           // a_max_size is 7

    /* copy construction */
    constexpr auto a_copy_c = a;
    auto a_copy = a;

    /* move construction */
    auto a_move = std::move(a_copy);

    /* copy assignment */
    constexpr string8 b{ "1234", 4 };                   // b is "1234"
    string8 c{ "lmnopqrstuvxyz" };                      // c is "lmnopqr"
    string8 d{ "56789" };                               // d is "789". rest is truncated.
    c = b;                                              // now c is "1234"

    /* move assingment */
    c = std::move(d);                                   // c is "56789"

    /* using with string view */
    constexpr string8 e{ "abcdefghij", 10 };            // truncated. e is "abcdefg";
    constexpr auto e_sub_str = e.str().substr(0, 2);    // e_sub_str is "ab"
    constexpr auto e_length = e.length();               // e_length is 7

    /* comparison */
    constexpr string8 f{ "abcd" };
    constexpr string8 g{ "abcd" };
    constexpr string8 h{ "abcf" };
    constexpr auto i = (f == g);                        // i is true 
    constexpr auto j = (g == h);                        // j is false

    /* append */
    string8 k{ "abc" };                                 // k is "abc"
    k.append("d");                                      // k is "abcd"
    k.append("efghi", 5);                               // k is "abcdefg". rest is truncated

    /* clear */
    k.clear();                                          // k is empty() ""
    auto k_empty = k.empty();                           // k_empty is true

    /* reset */
    k.reset("1234");                                    // k is "1234";
    auto k_length = k.length();                         // k_length is 4
    k.reset("xyz", 3);                                  // k is "xyz"

    /* remove_suffix */
    /* there is no boundary check. similar to string_view */
    string8 l{ "1234567" };
    l.remove_suffix(3);                                 // l is "1234"

    /* remove_prefix */
    /* there is no boundary check. similar to string_view */
    l.remove_prefix(2);                                 // l is "34"

    /* stream operator */
    std::cout << l << std::endl;

    /* using for member variables */
    struct test_struct
    {
        std::uint32_t a_{};
        std::uint64_t b_{};
        string8 c_{ "abcd" };                           // uses only 8 + 4 bytes in stack

        constexpr auto get_c() const { return c_.str(); }
        constexpr void set_c(const char* str) { c_.reset(str); }
    };

    auto test_struct_size = sizeof(test_struct);
    constexpr test_struct t;
    constexpr auto t_a = t.get_c();

    /* swap */
    l.swap(k);                                          // l is "xyz" and k is "34"
    swap(l, k);                                         // l is "34" and k is "xyz"
}