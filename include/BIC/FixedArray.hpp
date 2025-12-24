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

namespace detail
{
	
template<typename T, T VALUE, T FIRST_VALUE, T... OTHER_VALUES>
struct FixedArrayContains : Fixed<bool, VALUE == FIRST_VALUE or FixedArrayContains<T, VALUE, OTHER_VALUES...>::value> {};

template<typename T, T VALUE, T FIRST_VALUE>
struct FixedArrayContains<T, VALUE, FIRST_VALUE> : Fixed<bool, VALUE == FIRST_VALUE> {};
	
} // namespace detail

template<typename T, T VALUE, T... VALUES>
constexpr Fixed< bool, detail::FixedArrayContains<T, VALUE, VALUES...>::value > contains(const FixedArray<T, VALUES...>, const Fixed<T, VALUE>) { return {}; }

namespace detail
{

template<typename LhsArray, typename RhsArray>
struct FixedArraySubstract;

template<typename T, T FIRST_LHS_VALUE, T... OTHER_LHS_VALUES, T... RHS_VALUES>
struct FixedArraySubstract< FixedArray<T, FIRST_LHS_VALUE, OTHER_LHS_VALUES...>, FixedArray<T, RHS_VALUES...> >
{
	using FirstValueInRhs    = typename FixedArraySubstract< FixedArray<T, OTHER_LHS_VALUES...>, FixedArray<T, RHS_VALUES...> >::Type;
	using FirstValueNotInRhs = decltype(cat(fixed<T, FIRST_LHS_VALUE>, FirstValueInRhs{}));

	using Type = std::conditional_t<detail::FixedArrayContains<T, FIRST_LHS_VALUE, RHS_VALUES...>::value, 
		FirstValueInRhs,
		FirstValueNotInRhs>;
};

template<typename T, T LHS_VALUE, T... RHS_VALUES>
struct FixedArraySubstract< FixedArray<T, LHS_VALUE>, FixedArray<T, RHS_VALUES...> >
{
	using Type = std::conditional_t<detail::FixedArrayContains<T, LHS_VALUE, RHS_VALUES...>::value, 
		FixedArray<T>,
		FixedArray<T, LHS_VALUE>>;
};

} // namespace detail

template<typename T, T... LHS_VALUES, T... RHS_VALUES>
constexpr typename FixedArraySubstract< FixedArray<T, LHS_VALUES...>, FixedArray<T, RHS_VALUES...> >::Type substract(const FixedArray<T, LHS_VALUES...>, const FixedArray<T, RHS_VALUES...>) { return {}; }

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
constexpr FixedArrayElement<I, T, VALUES...> get(const FixedArray<T, VALUES...>) { return {}; }

/**
 * @brief Concatenate two Fixed.
 *
 * @tparam T          Scalar type.
 * @tparam LHS_VALUE  Value to prepend.
 * @tparam RHS_VALUE  Value to append.
 *
 * @param value A Fixed containing the value to prepend.
 * @param array A Fixed containing the value to append.
 * @return A new `FixedArray<T, lhsValue, rhsValue>` inserted at the end.
 */
template<typename T, T LHS_VALUES, T RHS_VALUE>
constexpr FixedArray<T, lhsValue, rhsValue> cat(const Fixed<T, LHS_VALUES>, const Fixed<T, RHS_VALUE>) { return {}; } 

/**
 * @brief Concatenate a FixedArray and a Fixed.
 *
 * @tparam T         Scalar type.
 * @tparam VALUES    Values to prepend.
 * @tparam NEW_BACK  Value to append.
 *
 * @param value A FixedArray containing the values to prepend.
 * @param array A Fixed containing the value to append.
 * @return A new FixedArray with `newBack` inserted at the end.
 */
template<typename T, T NEW_BACK, T... VALUES> 
constexpr FixedArray<T, VALUES..., NEW_BACK> cat(const FixedArray<T, VALUES...>, Fixed<T, NEW_BACK>) { return {}; }

/**
 * @brief Concatenate a Fixed and a FixedArray.
 *
 * @tparam T         Scalar type.
 * @tparam NEW_FRONT Value to prepend.
 * @tparam VALUES    Values to append.
 *
 * @param value A Fixed containing the value to prepend.
 * @param array A FixedArray containing the values to append.
 * @return A new FixedArray with `newFront` inserted at the beginning.
 */
template<typename T, T NEW_FRONT, T... VALUES> 
constexpr FixedArray<T, NEW_FRONT, VALUES...> cat(Fixed<T,NEW_FRONT>, const FixedArray<T, VALUES...>) { return {}; }

/**
 * @brief Concatenate two FixedArray.
 *
 * @tparam T          Scalar type.
 * @tparam LHS_VALUES Values to prepend.
 * @tparam RHS_VALUES Values to append.
 *
 * @param value A FixedArray containing the values to prepend.
 * @param array A FixedArray containing the values to append.
 * @return A new FixedArray with `lhsValues` inserted at the beginning.
 */
template<typename T, T... LHS_VALUES, T... RHS_VALUES>
constexpr FixedArray<T, LHS_VALUES..., RHS_VALUES...> cat(FixedArray<T, LHS_VALUES...> /* lhs */, FixedArray<T, RHS_VALUES...> /* rhs */) { return {}; }

} // namespace BIC

#endif // BIC_FIXED_ARRAY_HPP

