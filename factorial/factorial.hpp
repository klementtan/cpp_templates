#include <cstdint>

template<std::uint64_t n>
struct factorial {
  enum { value = n*factorial<n-1>::value };
};

template<>
struct factorial<0> {
  enum { value = 1 };
};
