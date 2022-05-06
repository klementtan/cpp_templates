namespace k {

template<bool Enabled, typename T = void>
struct enable_if;

template<typename T>
struct enable_if<true, T> {
  typedef T type;
};

template<typename T>
struct enable_if<false, T> {
  // force substitution failure when trying to access enable_if::type
};

template<bool Enabled, typename T = void>
using enable_if_t = typename k::enable_if<Enabled, T>::type;
}

