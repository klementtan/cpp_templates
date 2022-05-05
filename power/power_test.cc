#include "power.hpp"
#include <gtest/gtest.h>

TEST(Power, Power) {
  static_assert(pow_slow<2, 16>::value == 65536, "2^16 equals to 65,536");
  static_assert(pow_slow<2, 0>::value == 1, "2^0 equals to 1");

  static_assert(pow<2, 16>::value == 65536, "2^16 equals to 65,536");
  static_assert(pow<2, 0>::value == 1, "2^0 equals to 1");

  static_assert(pow<2, 15>::value == 32768, "2^15 equals to 32768");
}
