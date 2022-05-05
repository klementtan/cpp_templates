cc_library(
  name = "pow",
  hdrs = ["power/power.hpp"]
)

cc_library(
  name = "factorial",
  hdrs = ["factorial/factorial.hpp"]
)

cc_test(
  name = "pow_test",
  size = "small",
  srcs = ["power/power_test.cc"],
  deps = ["@com_google_googletest//:gtest_main", ":pow"]
)

cc_test(
  name = "factorial_test",
  size = "small",
  srcs = ["factorial/factorial_test.cc"],
  deps = ["@com_google_googletest//:gtest_main", ":factorial"]
)
