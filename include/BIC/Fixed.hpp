#ifndef BIC_FIXED_HPP
#define BIC_FIXED_HPP

namespace BIC
{
	
template<typename T, T VALUE> 
struct Fixed 
{ 
	using Type = T;
	
    constexpr operator T() const { return VALUE; } 

    static constexpr T value = VALUE;
};
	
template<typename T, T VALUE> 
Fixed<T,VALUE> fixed = {}; 
	
} // BIC

#include <BIC/misc/ComparableTo.hpp>
#include <type_traits> // for std::common_type_t

template<typename Lhs, Lhs lhs, typename Rhs, Rhs rhs> 
constexpr BIC::Fixed<std::common_type_t<Lhs, Rhs>, lhs + rhs> operator+(const BIC::Fixed<Lhs, lhs>, const BIC::Fixed<Rhs, rhs>) { return {}; } 

template<typename Lhs, Lhs lhs, typename Rhs, Rhs rhs> 
constexpr BIC::Fixed<std::common_type_t<Lhs, Rhs>, lhs - rhs> operator-(const BIC::Fixed<Lhs, lhs>, const BIC::Fixed<Rhs, rhs>) { return {}; }

template<typename Lhs, Lhs lhs, typename Rhs, Rhs rhs> 
constexpr BIC::Fixed<std::common_type_t<Lhs, Rhs>, lhs * rhs> operator*(const BIC::Fixed<Lhs, lhs>, const BIC::Fixed<Rhs, rhs>) { return {}; }

template<typename Lhs, Lhs lhs, typename Rhs, Rhs rhs> 
constexpr BIC::Fixed<std::common_type_t<Lhs, Rhs>, lhs / rhs> operator/(const BIC::Fixed<Lhs, lhs>, const BIC::Fixed<Rhs, rhs>) { return {}; } 

template<typename T, T lhs, T rhs> 
constexpr BIC::Fixed<bool, lhs && rhs> operator&&(const BIC::Fixed<T, lhs>, const BIC::Fixed<T,rhs>) { return {}; } 

template<typename T, T lhs, T rhs> 
constexpr BIC::Fixed<bool, lhs || rhs> operator||(const BIC::Fixed<T, lhs>, const BIC::Fixed<T,rhs>) { return {}; } 

template<typename Lhs, Lhs lhs, BIC::misc::ComparableTo<Lhs> Rhs, Rhs rhs> 
constexpr BIC::Fixed<bool, lhs < rhs> operator<(const BIC::Fixed<Lhs, lhs>, const BIC::Fixed<Rhs,rhs>) { return {}; } 

template<typename Lhs, Lhs lhs, BIC::misc::ComparableTo<Lhs> Rhs, Rhs rhs> 
constexpr BIC::Fixed<bool, lhs <= rhs> operator<=(const BIC::Fixed<Lhs, lhs>, const BIC::Fixed<Rhs,rhs>) { return {}; } 

template<typename Lhs, Lhs lhs, BIC::misc::ComparableTo<Lhs> Rhs, Rhs rhs> 
constexpr BIC::Fixed<bool, (lhs > rhs)> operator>(const BIC::Fixed<Lhs, lhs>, const BIC::Fixed<Rhs,rhs>) { return {}; } 

template<typename Lhs, Lhs lhs, BIC::misc::ComparableTo<Lhs> Rhs, Rhs rhs> 
constexpr BIC::Fixed<bool, (lhs >= rhs)> operator>=(const BIC::Fixed<Lhs, lhs>, const BIC::Fixed<Rhs,rhs>) { return {}; } 

template<typename Lhs, Lhs lhs, BIC::misc::ComparableTo<Lhs> Rhs, Rhs rhs> 
constexpr BIC::Fixed<bool, lhs == rhs> operator==(const BIC::Fixed<Lhs, lhs>, const BIC::Fixed<Rhs,rhs>) { return {}; } 

template<typename Lhs, Lhs lhs, BIC::misc::ComparableTo<Lhs> Rhs, Rhs rhs> 
constexpr BIC::Fixed<bool, lhs != rhs> operator!=(const BIC::Fixed<Lhs, lhs>, const BIC::Fixed<Rhs,rhs>) { return {}; } 


#endif // BIC_FIXED_HPP
