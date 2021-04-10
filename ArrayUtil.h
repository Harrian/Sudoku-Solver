/* file ArrayUtil.h */

#ifndef ARRAYUTIL_H
#define ARRAYUTIL_H

#include <array>

template <typename T, std::size_t N, std::size_t... I>
std::array<T, N> init_array_implementation(const T & to_repeat, std::index_sequence<I...>)
{
  return std::array<T, N> {(I, to_repeat)...};
}

template <typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
std::array<T, N> init_array(const T & to_repeat)
{
  std::array<T, N> ret = init_array_implementation<T, N>(to_repeat, Indices{});
  return ret;
}

#endif /* ARRAYUTIL_H */
