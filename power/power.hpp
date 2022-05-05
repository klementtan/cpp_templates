#include <cstddef>
#include <type_traits>


template<int x, std::size_t n>
struct pow_slow {
  enum { value = pow_slow<x, n-1>::value*x };
};

template<std::size_t x>
struct pow_slow<x, 0> {
  enum { value = 1 };
};


template<int x, std::size_t n, class Enable = void>
struct pow;

template<int x, std::size_t n>
struct pow<x, n, std::enable_if_t<n % 2 == 0 && n != 0>> {
  static const int half_value = pow<x, n/2>::value;
  enum {
    value = half_value*half_value
  };
};

template<int x, std::size_t n>
struct pow<x, n, std::enable_if_t<n % 2 != 0>> {
  enum {
    value = pow<x, n-1>::value*x
  };
};

template<int x, class Enable>
struct pow<x, 0, Enable> {
  enum {
    value = 1
  };
};
