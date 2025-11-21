#ifndef BIC_FIXED_HPP
#define BIC_FIXED_HPP

/**
 * @file Fixed.hpp
 * @brief Defines a compile-time constant wrapper type and arithmetic operators.
 * @date 2025
 * @version 1.0
 *
 * The `BIC::Fixed` struct provides a lightweight and strongly typed mechanism
 * for representing constant values as distinct types at compile time.
 * 
 * A `Fixed<T, VALUE>` behaves like a `constexpr T` but also carries its value
 * in its type — allowing powerful template metaprogramming and symbolic
 * compile-time arithmetic.
 *
 * This header also defines constexpr operator overloads that allow `Fixed`
 * instances to be combined with other `Fixed` constants, yielding new
 * `Fixed` types that encode the result in their template parameters.
 *
 * Example:
 * @code
 * using A = BIC::Fixed<int, 3>;
 * using B = BIC::Fixed<int, 5>;
 * 
 * constexpr auto sum = A{} + B{};     // Fixed<int, 8>
 * constexpr auto cmp = (A{} < B{});   // Fixed<bool, true>
 * 
 * static_assert(sum.value == 8);
 * static_assert(decltype(cmp)::value); // true
 * @endcode
 */
 
#include <BIC/misc/ComparableTo.hpp>
#include <type_traits> // for std::common_type_t
#include <concepts>
 
namespace BIC
{
	
/**
 * @brief Represents a compile-time fixed constant of type `T` with value `VALUE`.
 *
 * @tparam T      Underlying value type.
 * @tparam VALUE  Compile-time constant value.
 *
 * This structure behaves as a constant wrapper around a literal value.
 * It can be implicitly converted to `T`, and its `value` member provides
 * access to the compile-time constant.
 */
template<typename T, T VALUE> 
struct Fixed 
{ 
	using Type = T; ///<  @brief Underlying (non-fixed) type.
	
    constexpr operator Type() const { return VALUE; } ///<  @brief Implicit conversion to the underlying value type.

    static constexpr Type value = VALUE; ///<  @brief Compile-time constant value.
};

/**
 * @brief Global inline instance of `BIC::Fixed` for direct variable-style access.
 *
 * @tparam T      Underlying value type.
 * @tparam VALUE  Compile-time constant value.
 *
 * Example:
 * @code
 * auto x = BIC::fixed<int, 42>; // x is a Fixed<int, 42>
 * @endcode
 */
template<typename T, T VALUE> 
Fixed<T,VALUE> fixed = {}; 

// ============================================================================
// Counter operators
// ============================================================================

template<std::integral I, I i>      constexpr Fixed<I,i+1> next(const Fixed<I,i>) { return{}; }
template<std::integral I, I i>      constexpr Fixed<I,i-1> prev(const Fixed<I,i>) { return{}; }

template<std::integral I, I i, I j> constexpr Fixed<I,j-i> distance(const Fixed<I,i>, const Fixed<I,j>) { return{}; }

// ============================================================================
// Arithmetic operators for Fixed
// ============================================================================

template<typename Lhs, Lhs lhs, typename Rhs, Rhs rhs> 
constexpr Fixed<std::common_type_t<Lhs, Rhs>, lhs + rhs> operator+(const Fixed<Lhs, lhs>, const Fixed<Rhs, rhs>) { return {}; } 

template<typename Lhs, Lhs lhs, typename Rhs, Rhs rhs> 
constexpr Fixed<std::common_type_t<Lhs, Rhs>, lhs - rhs> operator-(const Fixed<Lhs, lhs>, const Fixed<Rhs, rhs>) { return {}; }

template<typename Lhs, Lhs lhs, typename Rhs, Rhs rhs> 
constexpr Fixed<std::common_type_t<Lhs, Rhs>, lhs * rhs> operator*(const Fixed<Lhs, lhs>, const Fixed<Rhs, rhs>) { return {}; }

template<typename Lhs, Lhs lhs, typename Rhs, Rhs rhs> 
constexpr Fixed<std::common_type_t<Lhs, Rhs>, lhs / rhs> operator/(const Fixed<Lhs, lhs>, const Fixed<Rhs, rhs>) { return {}; } 

// ============================================================================
// Logical operators for Fixed
// ============================================================================

template<typename T, T lhs, T rhs> 
constexpr Fixed<bool, lhs && rhs> operator&&(const Fixed<T, lhs>, const Fixed<T,rhs>) { return {}; } 

template<typename T, T lhs, T rhs> 
constexpr Fixed<bool, lhs || rhs> operator||(const Fixed<T, lhs>, const Fixed<T,rhs>) { return {}; } 

// ============================================================================
// Comparison operators for Fixed
// ============================================================================

template<typename Lhs, Lhs lhs, misc::ComparableTo<Lhs> Rhs, Rhs rhs> 
constexpr Fixed<bool, lhs < rhs> operator<(const Fixed<Lhs, lhs>, const Fixed<Rhs,rhs>) { return {}; } 

template<typename Lhs, Lhs lhs, misc::ComparableTo<Lhs> Rhs, Rhs rhs> 
constexpr Fixed<bool, lhs <= rhs> operator<=(const Fixed<Lhs, lhs>, const Fixed<Rhs,rhs>) { return {}; } 

template<typename Lhs, Lhs lhs, misc::ComparableTo<Lhs> Rhs, Rhs rhs> 
constexpr Fixed<bool, (lhs > rhs)> operator>(const Fixed<Lhs, lhs>, const Fixed<Rhs,rhs>) { return {}; } 

template<typename Lhs, Lhs lhs, misc::ComparableTo<Lhs> Rhs, Rhs rhs> 
constexpr Fixed<bool, (lhs >= rhs)> operator>=(const Fixed<Lhs, lhs>, const Fixed<Rhs,rhs>) { return {}; } 

template<typename Lhs, Lhs lhs, misc::ComparableTo<Lhs> Rhs, Rhs rhs> 
constexpr Fixed<bool, lhs == rhs> operator==(const Fixed<Lhs, lhs>, const Fixed<Rhs,rhs>) { return {}; } 

template<typename Lhs, Lhs lhs, misc::ComparableTo<Lhs> Rhs, Rhs rhs> 
constexpr Fixed<bool, lhs != rhs> operator!=(const Fixed<Lhs, lhs>, const Fixed<Rhs,rhs>) { return {}; } 

} // BIC

#endif // BIC_FIXED_HPP
