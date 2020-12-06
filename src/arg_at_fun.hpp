#ifndef ARGS_AT_FUN
#define ARGS_AT_FUN
#include <functional>

namespace abama_ss {
namespace core {
template <int index, typename T> struct arg_at_functions {};

template <typename return_type, typename arg>
struct arg_at_functions<0, return_type (*)(arg)> {
  using type = arg;
};

template <int index, typename return_type, typename arg, typename... args>
struct arg_at_functions<index, return_type (*)(arg, args...)> {
  using type =
      typename arg_at_functions<index - 1, return_type (*)(args...)>::type;
};
} // namespace core
} // namespace abama_ss
#endif