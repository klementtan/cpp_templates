cc_library(
  name = "pow",
  hdrs = ["power/power.hpp"]
)

cc_test(
  name = "pow_test",
  size = "small",
  srcs = ["power/power_test.cc"],
  deps = ["@com_google_googletest//:gtest_main", ":pow"]
)
