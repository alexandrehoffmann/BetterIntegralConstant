#ifndef BIC_SWITCH_HPP
#define BIC_SWITCH_HPP

#include <BIC/Fixed.hpp>
#include <BIC/FixedArray.hpp>
#include <BIC/Seq.hpp>

#include <utility>

namespace BIC
{

template<typename T, T... CASES, typename UnaryFunc>
constexpr switchCase(FixedArray<T, CASES...>, T targetCase, UnaryFunc&& func) { ((targetCase == CASES and (func(fixed<T, CASES>), true)) or ...); return std::forward<UnaryFunc>(func); }

template<typename Size, Size FIRST_CASE, Size BOUND_CASE, typename UnaryFunc> 
constexpr switchCase(Fixed<Size, FIRST_CASE>, Fixed<Size, BOUND_CASE>, Size targetCase, UnaryFunc&& func) { return switchCase(seq<Size, FIRST, BOUND>, std::forward<UnaryFunc>(func)); }
	
} // namespace BIC

#endif // BIC_SWITCH_HPP
