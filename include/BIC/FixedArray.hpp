#ifndef BIC_FIXED_ARRAY_HPP
#define BIC_FIXED_ARRAY_HPP

#include <BIC/Fixed.hpp>

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
	
	constexpr operator Type() const { return {VALUES...}; }  ///<  @brief Implicit conversion operator to the underlying std::array.
	
	static constexpr Type                             values = {VALUES...}; ///<  @brief Compile-time array of the stored values.
	static constexpr Fixed<size_t, sizeof...(VALUES)> size   = {};          ///<  @brief Number of stored elements.
	
	constexpr const Scalar& operator[](const size_t i) const { return values[i]; }
	
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
 * @brief Append a scalar value to the back of a FixedArray.
 *
 * @tparam T       Scalar type.
 * @tparam newBack Value to append.
 * @tparam values  Existing array values.
 *
 * @param array A FixedArray of existing values.
 * @param value A Fixed<T,newBack> wrapper containing the value to append.
 * @return A new FixedArray with `newBack` appended at the end.
 */
template<typename T, T newBack, T... values> 
FixedArray<T, values..., newBack> append(const FixedArray<T, values...>, Fixed<T,newBack>) { return {}; }

/**
 * @brief Append a scalar value to the front of a FixedArray.
 *
 * @tparam T        Scalar type.
 * @tparam newFront Value to prepend.
 * @tparam values   Existing array values.
 *
 * @param value A Fixed<T,newFront> wrapper containing the value to prepend.
 * @param array A FixedArray of existing values.
 * @return A new FixedArray with `newFront` inserted at the beginning.
 */
template<typename T, T newFront, T... values> 
FixedArray<T, newFront, values...> append(Fixed<T,newFront>, const FixedArray<T, values...>) { return {}; }

namespace detail
{
	template<size_t I, typename T, T... VALUES> struct FixedArrayElementHelper;

    template<size_t I, typename T, T FIRST_VALUE, T... OTHER_VALUES> requires(I != 0)
    struct FixedArrayElementHelper<I, T, FIRST_VALUE, OTHER_VALUES...>
    {
        using Type = typename FixedArrayElementHelper<I-1, T, OTHER_VALUES...>::Type;
    };

    template<size_t I, typename T, T FIRST_VALUE, T... OTHER_VALUES> requires(I == 0)
    struct FixedArrayElementHelper<I, T, FIRST_VALUE, OTHER_VALUES...>
    {
        using Type = Fixed<T, FIRST_VALUE>;
    };
} // namespace detail

/**
 * @brief Retrieve the type of the `I`th Fixed from a FixedArray.
 *
 * @tparam I      Index to retrieve (must be zero).
 * @tparam T      Scalar type.
 * @tparam values elements.
 *
 * @param array The FixedArray instance (passed for type deduction).
 */
template<size_t I, typename T, T... VALUES>
using FixedArrayElement = typename detail::FixedArrayElementHelper<I, T, VALUES...>::Type;

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


} // namespace BIC

#endif // BIC_FIXED_ARRAY_HPP

