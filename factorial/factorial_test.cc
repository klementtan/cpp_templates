#include "factorial.hpp"
#include <gtest/gtest.h>

TEST(Factorial, Factorial) {
  static_assert(factorial<0>::value == 1, "0! == 1");
  static_assert(factorial<1>::value == 1, "1! == 1");
  static_assert(factorial<10>::value == 3628800, "10! == 3628800");
}
