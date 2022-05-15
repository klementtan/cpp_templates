cc_library(
  name = "pow",
  hdrs = ["power/power.hpp"]
)

cc_library(
  name = "factorial",
  hdrs = ["factorial/factorial.hpp"]
)

cc_library(
  name = "enable_if",
  hdrs = ["enable_if/enable_if.hpp"]
)

cc_library(
  name = "crtp_new_handler",
  hdrs = ["crtp_new_handler/crtp_new_handler.hpp"]
)

cc_library(
  name = "shared_ptr",
  hdrs = ["shared_ptr/shared_ptr.hpp"]
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

cc_test(
  name = "enable_if_test",
  size = "small",
  srcs = ["enable_if/enable_if_test.cc"],
  deps = ["@com_google_googletest//:gtest_main", ":enable_if"]
)

cc_test(
  name = "crtp_new_handler_test",
  size = "small",
  srcs = ["crtp_new_handler/crtp_new_handler_test.cc"],
  deps = ["@com_google_googletest//:gtest_main", ":crtp_new_handler"]
)

cc_test(
  name = "shared_ptr_test",
  size = "small",
  srcs = ["shared_ptr/shared_ptr_test.cc"],
  deps = ["@com_google_googletest//:gtest_main", ":shared_ptr"]
)
