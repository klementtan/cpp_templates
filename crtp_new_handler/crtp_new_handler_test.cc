#include "crtp_new_handler.hpp"
#include <cstdlib>
#include <gtest/gtest.h>
#include <limits>

template<std::size_t N>
struct Foo : NewHandlerSupport<Foo<N>>{
  uint64_t nums[N];
};

size_t oom_call_count = 0;

void oom_handler() {
  oom_call_count++;
  throw std::bad_alloc();
}

TEST(CrtpNewHandler, CrtpNewHandler) {
  // large N to force OOM
  constexpr size_t large_count = 1e12;
  Foo<large_count>::set_hanlder(oom_handler);
  try {
    new Foo<large_count>[1000];
  } catch (...) {
  }
  // Should call OOM handler
  ASSERT_EQ(oom_call_count, 1);

  // should not call OOM handler for other class
  try {
    new Foo<large_count-10>[1000];
  } catch(...) {}
  ASSERT_EQ(oom_call_count, 1);

}
