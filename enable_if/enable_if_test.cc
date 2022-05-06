#include "enable_if.hpp"
#include <gtest/gtest.h>

template<typename T>
k::enable_if_t<std::is_integral_v<T>, std::string> foo(T t) {
  return "is integral";
}

template<typename T>
k::enable_if_t<!std::is_integral_v<T>, std::string> foo(T t) {
  return "not integral";
}

TEST(EnableIf, EnableIf) {
  ASSERT_EQ(foo(1), "is integral");
  ASSERT_EQ(foo("bar"), "not integral");
}
