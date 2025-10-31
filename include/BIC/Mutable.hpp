#ifndef BIC_MUTABLE_HPP
#define BIC_MUTABLE_HPP

/**
 * @file Mutable.hpp
 * @brief Type trait that extracts the underlying non-fixed type of a given type.
 * @date 2025
 * @version 1.0
 *
 * The `BIC::Mutable` type alias provides a convenient way to obtain
 * the non-constant (mutable) form of a type that may be wrapped in
 * a compile-time `BIC::Fixed` or `BIC::IsFixed` type.
 *
 * It relies on internal `detail::MutableTraits` specializations to determine
 * the correct base type. This is useful for writing template code that can
 * operate transparently on both compile-time fixed constants and regular
 * runtime variables.
 *
 * Example:
 * @code
 * using A = BIC::Fixed<int, 3>;
 * using B = BIC::Mutable<A>;       // int
 * using C = BIC::Mutable<double>;  // double
 * using D = BIC::Mutable<BIC::IsFixed<int>>; // bool
 * @endcode
 */
 
namespace BIC
{
	
namespace detail
{

template<typename T>
struct MutableTraits
{
    using Type = T;
};

template<typename T, T VALUE> 
struct MutableTraits<Fixed<T,VALUE>>
{
    using Type = T;
};

template<typename T> 
struct MutableTraits<IsFixed<T>>
{
    using Type = bool;
};

} // namespace detail

/**
 * @brief Type alias for obtaining the mutable (non-fixed) type of `T`.
 *
 * @tparam T The type to make mutable.
 *
 * This alias resolves to the underlying base type of `T`
 * by applying `detail::MutableTraits`.
 *
 * Example:
 * @code
 * using A = BIC::Fixed<int, 7>;
 * BIC::Mutable<A> value = 0; // type is int
 * @endcode
 */
template<typename T>
using Mutable = typename detail::MutableTraits<T>::Type;
	
} // namespace BIC

#endif // BIC_MUTABLE_HPP
