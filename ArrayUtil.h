/* file ArrayUtil.h */

#ifndef ARRAYUTIL_H
#define ARRAYUTIL_H

#include <array>
#include <cstdint>
#include <cstddef>
#include <cstring>

/*
 * Would work for some non integer types but for safety just do integer types
 */
template <typename T, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T>>>
std::array<std::array<T, N>, N> const_to_non_const_copy(const std::array<const std::array<T, N>, N> & original_data)
{
  std::array<std::array<T, N>, N> ret;

  for(std::size_t i = 0; i < N; i++)
  {
    std::memcpy(ret[i].data(), original_data[i].data(), N * sizeof(T));
  }

  return ret;
}

/*
 * Would work for some non integer types but for safety just do integer types
 */
template <typename T, std::size_t N, std::size_t... I, typename = std::enable_if_t<std::is_integral_v<T>>>
std::array<const std::array<T, N>, N> move_into_const(std::array<std::array<T, N>, N> & to_move, std::index_sequence<I...>)
{
  return std::array<const std::array<T, N>, N> {std::move(to_move[I])...};
}

template <typename T, std::size_t N, typename Indices = std::make_index_sequence<N>, typename = std::enable_if_t<std::is_integral_v<T>>>
std::array<const std::array<T, N>, N> non_const_to_const_copy(const std::array<std::array<T, N>, N> & original_data)
{
  std::array<std::array<T, N>, N> clone;

  for(std::size_t i = 0; i < N; i++)
  {
    std::memcpy(clone[i].data(), original_data[i].data(), N * sizeof(T));
  }

  //std::array<const std::array<T, N>, N> ret{std::move(clone[0]) ... std::move(clone(N-1))};
  std::array<const std::array<T, N>, N> ret = move_into_const(clone, Indices{});

  return ret;
}

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
