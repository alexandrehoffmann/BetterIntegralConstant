#ifndef BIC_FIXED_ARRAY_ELEMENT_HPP
#define BIC_FIXED_ARRAY_ELEMENT_HPP

#include <BIC/Fixed.hpp>

namespace BIC
{

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

} // namespace BIC

#endif // BIC_FIXED_ARRAY_ELEMENT_HPP
