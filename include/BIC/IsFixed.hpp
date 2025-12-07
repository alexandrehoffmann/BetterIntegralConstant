#ifndef BIC_IS_FIXED_HPP
#define BIC_IS_FIXED_HPP

/**
 * @file IsFixed.hpp
 * @brief Type trait for detecting whether a type is a BIC::Fixed constant.
 * @date 2025
 * @version 1.0
 *
 * This header defines the `BIC::IsFixed` type trait and the helper function
 * `BIC::isFixed()`, which determine whether a given type is a specialization
 * of `BIC::Fixed`.
 *
 * Example:
 * @code
 * using A = BIC::Fixed<int, 3>;
 * static_assert(BIC::IsFixed<A>::value);      // true
 * static_assert(!BIC::IsFixed<double>::value); // false
 * @endcode
 *
 * The trait itself derives from `BIC::Fixed<bool, true/false>` for convenient
 * compile-time evaluation and integration with other BIC metaprogramming tools.
 */
 
namespace BIC
{
	
/**
 * @brief Default case: `T` is not a fixed constant type.
 * 
 * @tparam T Arbitrary type to test.
 *
 * In this general case, `IsFixed<T>` inherits from `Fixed<bool, false>`,
 * indicating that `T` is not a specialization of `BIC::Fixed`.
 */
template<typename T> 
struct IsFixed : Fixed<bool, false> {}; 

/**
 * @brief Specialization for types that are instances of `BIC::Fixed`.
 *
 * @tparam T    Underlying type of the fixed constant.
 * @tparam value The compile-time constant value of the `Fixed` type.
 *
 * This specialization inherits from `Fixed<bool, true>`, indicating that
 * the tested type is indeed a `BIC::Fixed`.
 */
template<typename T, T value> 
struct IsFixed<Fixed<T, value>> : Fixed<bool, true> {};  

/**
 * @brief Recursive specialization: `IsFixed` of an `IsFixed` is still `true`.
 *
 * @tparam T The nested type parameter.
 *
 * This ensures that nested applications of `IsFixed` (e.g., `IsFixed<IsFixed<T>>`)
 * consistently evaluate to `true`.
 */
template<typename T> 
struct IsFixed<IsFixed<T>> : Fixed<bool, true> {}; 

template<typename T>
concept Fixed_concept = IsFixed<T>::value;

/**
 * @brief Helper constexpr function to create an `IsFixed` object from a value.
 *
 * @tparam T Type of the input value.
 * @param  value The value to test (unused).
 * @return constexpr IsFixed<T> A compile-time object representing whether `T` is fixed.
 *
 * Example:
 * @code
 * BIC::Fixed<int, 4> x{};
 * auto flag = BIC::isFixed(x); // returns IsFixed<Fixed<int,4>> → true
 * @endcode
 */
template <typename T> constexpr IsFixed<T> isFixed(const T&) { return {}; }
	
} // BIC

#endif // BIC_IS_FIXED_HPP
