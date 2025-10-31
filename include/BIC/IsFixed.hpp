#ifndef BIC_IS_FIXED_HPP
#define BIC_IS_FIXED_HPP

namespace BIC
{
	
template<typename T> 
struct IsFixed : Fixed<bool, false> {}; 

template<typename T, T value> 
struct IsFixed<Fixed<T, value>> : Fixed<bool, true> {};  

template<typename T> 
struct IsFixed<IsFixed<T>> : Fixed<bool, true> {}; 

template <typename T> constexpr IsFixed<T> isFixed(const T&) { return {}; }
	
} // BIC

#endif // BIC_IS_FIXED_HPP
