# FastString
**Fast, in stack, fixed size** string implementation with **constexpr noexcept** constructors and accessors. **FastString** improves **memory locality and latency** of strings by avoiding heap allocations.

## Abstract
**std::string** allocates heap memory for strings not qualified for **SSO** (small string optimization) and reduces memory locality. **FastString** is a thin wrapper around a plain char array with **constexpr noexcept** constructors and accessors for fast, in stack string manipulation. **FastString** is a fast and efficient alternative for **std::string** or **plain char arrays** in low latency applications and can be easily used with **std::string_view** for further operations.


## Requirements	
* C++20 compatible compiler (constexpr std::copy is required for constexpr constructors)
* Works with 
   * **Microsoft (R) C/C++ Optimizing Compiler Version 19.27.29111** or above
   * **x86-64 gcc-trunk**

## Build
```console
mkdir build && cd build && cmake .. && make
```

## Performance
* Compiler version:MSVC 19.28.29334.0
* Using Google Benchmark (Tests are included in repo)
```console
Run on (8 X 1498 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x4)
  L1 Instruction 32 KiB (x4)
  L2 Unified 512 KiB (x4)
  L3 Unified 8192 KiB (x1)
--------------------------------------------------------------------------------------
Benchmark                                            Time             CPU   Iterations
--------------------------------------------------------------------------------------
BM_std_string_from_const_char                      498 ns          148 ns      5600000
BM_fixed_size_str_from_const_char                 46.9 ns         16.3 ns     34461538
BM_std_string_from_constexpr_const_char            500 ns          153 ns      4480000
BM_fixed_size_str_from_constexpr_const_char       47.8 ns         16.7 ns     37333333
BM_std_string_from_buffer                          505 ns          158 ns      5146257
BM_fixed_size_str_from_buffer                     49.6 ns         14.2 ns     37333333
BM_std_string_from_constexpr_buffer                503 ns          188 ns      4072727
BM_fixed_size_str_from_constexpr_buffer           50.1 ns         12.6 ns     44800000
BM_std_string_from_const_char_large_str           1048 ns          384 ns      2240000
BM_fixed_size_str_from_const_char_large_str        153 ns         50.0 ns     10000000
BM_std_string_append                               190 ns         62.5 ns     10000000
BM_fixed_size_str_append                           164 ns         56.2 ns     14451613
BM_std_string_append_large                        50.0 ns         16.4 ns     64000000
BM_fixed_size_str_append_large                    61.5 ns         23.4 ns     37333333
```

* Compiler version: **x86-64 gcc-trunk**
* Test scenario - Function creates a string from a given char pointer and return length of the created string. Length is returned and assigned to a volatile variable to avoid compiler optimizing out the construction of the variable.
* Test code 
    * Using **std::string**
        ```cpp
        auto f(const char* str)
        {
            std::string a{str};
            return a.length();
        }

        void g(const char* str)
        {
            volatile auto x = f(str);
        }
        ```
    * Using **FastString**. Note use of **constexpr** and **noexcept**
        ```cpp
        constexpr auto f(const char* str) noexcept
        {
            using string64 = fss::fixed_size_str<63>;
            string64 a{str};
            return a.length(); 
        }

        void g(const char* str)
        {
            volatile auto x = f(str);
        }
        ```        
* Comparison of compiler output between **std::string** and **FastString** using https://godbolt.org/
	![image](https://github.com/m3janitha/FastString/blob/master/compiler_analysis.jpg)

## Usage
Refer to below example code
```cpp
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
```

