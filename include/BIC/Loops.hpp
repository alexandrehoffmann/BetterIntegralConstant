#ifndef BIC_LOOPS_HPP
#define BIC_LOOPS_HPP

#include <BIC/Fixed.hpp>
#include <BIC/FixedArray.hpp>
#include <BIC/Seq.hpp>

#include <tuple>
#include <utility>

namespace BIC
{

template <typename T, T... VALUES, typename UnaryFunc>
constexpr UnaryFunc&& foreach(FixedArray<T, VALUES...>, UnaryFunc && func)
{
  (func(fixed<T, VALUES>), ...);
  return std::forward<UnaryFunc>(func);
}

template <typename Size, Size FIRST, Size BOUND, typename UnaryFunc>
constexpr UnaryFunc&& foreach(Fixed<Size, FIRST>, Fixed<Size, BOUND>, UnaryFunc && func)
{
  return foreach(seq<Size, FIRST, BOUND>, std::forward<UnaryFunc>(func));
}

template <typename Size, Size FIRST, Size BOUND, Size STEP, typename UnaryFunc>
constexpr UnaryFunc&& foreach(Fixed<Size, FIRST>, Fixed<Size, BOUND>, Fixed<Size, STEP>, UnaryFunc && func)
{
  return foreach(seq<Size, FIRST, BOUND, STEP>, std::forward<UnaryFunc>(func));
}

template <typename Tuple, typename UnaryFunc>
  requires requires { typename std::tuple_size<std::remove_reference_t<Tuple>>::type; }
constexpr UnaryFunc&& foreach(Tuple&& tuple, UnaryFunc && func)
{
  constexpr size_t N = std::tuple_size_v<std::remove_reference_t<Tuple>>;

  return foreach(fixed<size_t, 0ul>, fixed<size_t, N>, [=](const CFixed auto i) { return func(std::get<i>(tuple)); });

  return std::forward<UnaryFunc>(func);
}

} // namespace BIC

#endif // BIC_LOOPS_HPP
