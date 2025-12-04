#ifndef BIC_FIXED_ARRAY_HPP
#define BIC_FIXED_ARRAY_HPP

#include <BIC/Fixed.hpp>
#include <BIC/FixedArrayElement.hpp>

#include <array>
#include <cstddef> // for size_t

namespace BIC
{

/**
 * @brief A compile-time fixed array constructed from a parameter pack.
 *
 * `FixedArray` represents a constant array whose contents are fully known at
 * compile time. It provides a lightweight wrapper around `std::array`,
 * supporting iteration, indexing, and implicit conversion to the underlying
 * `std::array` type.
 *
 * @tparam T       Scalar type of the array elements.
 * @tparam VALUES  Parameter pack of compile-time constant values.
 */
template<typename T, T... VALUES> 
struct FixedArray
{
	using Scalar   = T;                                ///<  @brief Scalar value type.
	using Type     = std::array<T, sizeof...(VALUES)>; ///<  @brief The underlying std::array type.
	using Iterator = typename Type::const_iterator;    ///<  @brief Const iterator type for the underlying array.

	template<size_t I> using IthElement = FixedArrayElement<I, T, VALUES...>;

	constexpr operator Type() const { return {VALUES...}; }  ///<  @brief Implicit conversion operator to the underlying std::array.
	
	static constexpr Type                             values = {VALUES...}; ///<  @brief Compile-time array of the stored values.
	static constexpr Fixed<size_t, sizeof...(VALUES)> size   = {};          ///<  @brief Number of stored elements.
	static constexpr Fixed<bool, size == 0>           empty  = {};
	
	constexpr const Scalar& operator[](const size_t i) const { return values[i]; }

	template<size_t I> constexpr IthElement<I> operator[](const Fixed<size_t, I>) const { return {}; }
	
	constexpr Iterator begin() const { return std::begin(values); } 
	constexpr Iterator end()   const { return std::end(values); }
	
	constexpr Iterator cbegin() const { return std::begin(values); } 
	constexpr Iterator cend()   const { return std::end(values); } 
};

/**
 * @brief Convenience alias for a compile-time array of `size_t` indices.
 *
 * Useful for meta-programming utilities that operate on index lists.
 */
template<size_t... INDICES>
using FixedIndices = FixedArray<size_t, INDICES...>; 

/**
 * @brief Global constexpr instance for simple creation of FixedArray objects.
 *
 * Example:
 * @code
 * auto arr = fixedArray<int,1,2,3>;
 * @endcode
 */
template<typename T, T... VALUES> 
constexpr FixedArray<T, VALUES...> fixedArray = {};

/**
 * @brief Global constexpr instance for creating `FixedIndices`.
 */
template<size_t... INDICES>
constexpr FixedIndices<INDICES...> fixedIndices = {};

// ============================================================================
// Helper functions
// ============================================================================

/**
 * @brief Retrieve an element at index `I` from a FixedArray.
 *
 * @tparam I      Index to retrieve (must be zero).
 * @tparam T      Scalar type.
 * @tparam values elements.
 *
 * @param array The FixedArray instance (passed for type deduction).
 */
template<size_t I, typename T, T... VALUES>
FixedArrayElement<I, T, VALUES...> get(const FixedArray<T, VALUES...>) { return {}; }

/**
 * @brief Concatenate two Fixed.
 *
 * @tparam T         Scalar type.
 * @tparam lhsValue  Value to prepend.
 * @tparam rhsValue  Value to append.
 *
 * @param value A Fixed containing the value to prepend.
 * @param array A Fixed containing the value to append.
 * @return A new `FixedArray<T, lhsValue, rhsValue>` inserted at the end.
 */
template<typename T, T lhsValue, T rhsValue>
FixedArray<T, lhsValue, rhsValue> cat(const Fixed<T, lhsValue>, const Fixed<T, rhsValue>) { return {}; } 

/**
 * @brief Concatenate a FixedArray and a Fixed.
 *
 * @tparam T         Scalar type.
 * @tparam values    Values to prepend.
 * @tparam newBack   Value to append.
 *
 * @param value A FixedArray containing the values to prepend.
 * @param array A Fixed containing the value to append.
 * @return A new FixedArray with `newBack` inserted at the end.
 */
template<typename T, T newBack, T... values> 
FixedArray<T, values..., newBack> cat(const FixedArray<T, values...>, Fixed<T, newBack>) { return {}; }

/**
 * @brief Concatenate a Fixed and a FixedArray.
 *
 * @tparam T         Scalar type.
 * @tparam newFront  Value to prepend.
 * @tparam values    Values to append.
 *
 * @param value A Fixed containing the value to prepend.
 * @param array A FixedArray containing the values to append.
 * @return A new FixedArray with `newFront` inserted at the beginning.
 */
template<typename T, T newFront, T... values> 
FixedArray<T, newFront, values...> cat(Fixed<T,newFront>, const FixedArray<T, values...>) { return {}; }

/**
 * @brief Concatenate two FixedArray.
 *
 * @tparam T         Scalar type.
 * @tparam lhsValues Values to prepend.
 * @tparam rhsValues Values to append.
 *
 * @param value A FixedArray containing the values to prepend.
 * @param array A FixedArray containing the values to append.
 * @return A new FixedArray with `lhsValues` inserted at the beginning.
 */
template<typename T, T... lhsValues, T... rhsValues>
FixedArray<T, lhsValues..., rhsValues...> cat(FixedArray<T, lhsValues...> /* lhs */, FixedArray<T, rhsValues...> /* rhs */) { return {}; }

} // namespace BIC

#endif // BIC_FIXED_ARRAY_HPP

