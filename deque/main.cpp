#include <boost/container/devector.hpp>
#include <deque>
#include <vector>
#include <memory>
#include <benchmark/benchmark.h>


struct basic_structure {
  basic_structure(size_t d) : data{d} { md = std::make_unique<size_t>(d); }
  std::unique_ptr<size_t> md;
  std::string name = "empty";
  size_t data = 0;
};



static void bm_std_deque(benchmark::State& state) {

  std::deque<basic_structure> list;

  size_t d=0;
  for(size_t i=0; i < 5; ++i)
    list.emplace_back(basic_structure(++d));

  for (auto _ : state) {
    for(size_t i=0; i < 3; ++i)
      list.emplace_back(basic_structure(++d));
    for(size_t i=0; i < 3; ++i)
      list.pop_front();
  }
}
BENCHMARK(bm_std_deque);

static void bm_std_deque2(benchmark::State& state) {

  std::deque<basic_structure> list;

  size_t d=0;
  for(size_t i=0; i < 5; ++i)
    list.push_back(basic_structure(++d));

  for (auto _ : state) {
    for(size_t i=0; i < 3; ++i)
      list.push_back(basic_structure(++d));
    for(size_t i=0; i < 3; ++i)
      list.pop_front();
  }
}
BENCHMARK(bm_std_deque2);


static void bm_std_vector(benchmark::State& state) {

  std::vector<basic_structure> list;

  size_t d=0;
  for(size_t i=0; i < 5; ++i)
    list.emplace_back(basic_structure(++d));

  for (auto _ : state) {
    for(size_t i=0; i < 3; ++i)
      list.emplace_back(basic_structure(++d));
    for(size_t i=0; i < 3; ++i)
      list.erase(list.begin());
  }
}
BENCHMARK(bm_std_vector);

static void bm_boost_devector(benchmark::State& state) {

  boost::container::devector<basic_structure> list;

  size_t d=0;
  for(size_t i=0; i < 5; ++i)
    list.emplace_back(basic_structure(++d));

  for (auto _ : state) {
    for(size_t i=0; i < 3; ++i)
      list.emplace_back(basic_structure(++d));
    for(size_t i=0; i < 3; ++i)
      list.pop_front();
  }
}
BENCHMARK(bm_boost_devector);





BENCHMARK_MAIN();
