#ifndef BIC_LOOPS_HPP
#define BIC_LOOPS_HPP

#include <BIC/Fixed.hpp>
#include <BIC/FixedArray.hpp>
#include <BIC/Seq.hpp>

#include <utility>

namespace BIC
{
	
template<typename T, T... VALUES, typename UnaryFunc> 
constexpr UnaryFunc&& foreach(FixedArray<T, VALUES...>, UnaryFunc&& func) { (func(fixed<T,VALUES>), ...); return std::forward<UnaryFunc>(func); }
	
template<typename Size, Size FIRST, Size BOUND, typename UnaryFunc> 
constexpr UnaryFunc&& foreach(Fixed<Size, FIRST>, Fixed<Size, BOUND>, UnaryFunc&& func) { return foreach(seq<Size, FIRST, BOUND>, std::forward<UnaryFunc>(func)); }

template<typename Size, Size FIRST, Size BOUND, Size STEP, typename UnaryFunc> 
constexpr UnaryFunc&& foreach(Fixed<Size, FIRST>, Fixed<Size, BOUND>, Fixed<Size, STEP>, UnaryFunc&& func) { return foreach(seq<Size, FIRST, BOUND, STEP>, std::forward<UnaryFunc>(func)); }
	
} // namespace BIC

#endif // BIC_LOOPS_HPP
