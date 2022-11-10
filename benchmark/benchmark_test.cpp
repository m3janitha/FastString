#include <string>
#include <array>
#include <FastString.h>

#include <benchmark/benchmark.h>

// SSO applies for strings shoter than 22 on 64 systems

static void BM_std_string_from_const_char(benchmark::State& state) 
{
  const char* str = "Hello World!";
  for (auto _ : state) 
  {
        std::string a{str};
        benchmark::DoNotOptimize(a);
  }
}

BENCHMARK(BM_std_string_from_const_char);

static void BM_fixed_size_str_from_const_char(benchmark::State& state) 
{
  const char* str = "Hello World!";
  for (auto _ : state) 
  {
        fss::fixed_size_str<15> a{str};
        benchmark::DoNotOptimize(a);
  }
}

BENCHMARK(BM_fixed_size_str_from_const_char);

////////////////////////////////////////////////////////////////////////////////////////////////

static void BM_std_string_from_constexpr_const_char(benchmark::State& state) 
{
  constexpr const char* str = "Hello World!";
  for (auto _ : state) 
  {
        std::string a{str};
        benchmark::DoNotOptimize(a);
  }
}

BENCHMARK(BM_std_string_from_constexpr_const_char);

static void BM_fixed_size_str_from_constexpr_const_char(benchmark::State& state) 
{
  constexpr const char* str = "Hello World!";
  for (auto _ : state) 
  {
        fss::fixed_size_str<15> a{str};
        benchmark::DoNotOptimize(a);
  }
}

BENCHMARK(BM_fixed_size_str_from_constexpr_const_char);

////////////////////////////////////////////////////////////////////////////////////////////////


static void BM_std_string_from_buffer(benchmark::State& state) 
{
  std::array<char, 16> str = {'H', 'e', 'l', 'l' , 'o' , ' ' , 'W', 'o', 'r', 'l', 'd', '!', '\0' };
  for (auto _ : state) 
  {
        std::string a{str.data()};
        benchmark::DoNotOptimize(a);
  }
}

BENCHMARK(BM_std_string_from_buffer);

static void BM_fixed_size_str_from_buffer(benchmark::State& state) 
{
  std::array<char, 16> str = {'H', 'e', 'l', 'l' , 'o' , ' ' , 'W', 'o', 'r', 'l', 'd', '!', '\0' };
  for (auto _ : state) 
  {
        fss::fixed_size_str<15> a{str.data()};
        benchmark::DoNotOptimize(a);
  }
}

BENCHMARK(BM_fixed_size_str_from_buffer);

////////////////////////////////////////////////////////////////////////////////////////////////

static void BM_std_string_from_constexpr_buffer(benchmark::State& state) 
{
  constexpr std::array<char, 16> str = {'H', 'e', 'l', 'l' , 'o' , ' ' , 'W', 'o', 'r', 'l', 'd', '!', '\0' };
  for (auto _ : state) 
  {
        std::string a{str.data()};
        benchmark::DoNotOptimize(a);
  }
}

BENCHMARK(BM_std_string_from_constexpr_buffer);

static void BM_fixed_size_str_from_constexpr_buffer(benchmark::State& state) 
{
  constexpr std::array<char, 16> str = {'H', 'e', 'l', 'l' , 'o' , ' ' , 'W', 'o', 'r', 'l', 'd', '!', '\0' };
  for (auto _ : state) 
  {
        fss::fixed_size_str<15> a{str.data()};
        benchmark::DoNotOptimize(a);
  }
}

BENCHMARK(BM_fixed_size_str_from_constexpr_buffer);

////////////////////////////////////////////////////////////////////////////////////////////////

static void BM_std_string_from_const_char_large_str(benchmark::State& state) 
{
  const char* str = "fixed length string vs std string benchmark";
  for (auto _ : state) 
  {
        std::string a{str};
        benchmark::DoNotOptimize(a);
  }
}

BENCHMARK(BM_std_string_from_const_char_large_str);

static void BM_fixed_size_str_from_const_char_large_str(benchmark::State& state) 
{
  const char* str = "fixed length string vs std string benchmark";
  for (auto _ : state) 
  {
        fss::fixed_size_str<31> a{str};
        benchmark::DoNotOptimize(a);
  }
}

BENCHMARK(BM_fixed_size_str_from_const_char_large_str);

////////////////////////////////////////////////////////////////////////////////////////////////

static void BM_std_string_append(benchmark::State& state) 
{
  std::string a{"Hello"};
  const char* b = " fixed length string vs std string benchmark";
  for (auto _ : state) 
  {
        a.append(b);
        benchmark::DoNotOptimize(a);
  }
}

BENCHMARK(BM_std_string_append);

static void BM_fixed_size_str_append(benchmark::State& state) 
{
  fss::fixed_size_str<63> a{"Hello"};
  const char* b = " fixed length string vs std string benchmark";
  for (auto _ : state) 
  {
        a.append(b);
        benchmark::DoNotOptimize(a);
  }
}

BENCHMARK(BM_fixed_size_str_append);

////////////////////////////////////////////////////////////////////////////////////////////////

static void BM_std_string_append_large(benchmark::State& state) 
{
  std::string a{"Hello"};
  const char* b = " world";
  for (auto _ : state) 
  {
        a.append(b);
        benchmark::DoNotOptimize(a);
  }
}

BENCHMARK(BM_std_string_append_large);

static void BM_fixed_size_str_append_large(benchmark::State& state) 
{
  fss::fixed_size_str<15> a{"Hello"};
  const char* b = " world";
  for (auto _ : state) 
  {
        a.append(b);
        benchmark::DoNotOptimize(a);
  }
}

BENCHMARK(BM_fixed_size_str_append_large);

////////////////////////////////////////////////////////////////////////////////////////////////


BENCHMARK_MAIN();