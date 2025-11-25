#ifndef BIC_SEQ_HPP
#define BIC_SEQ_HPP

#include <BIC/FixedArray.hpp>

namespace BIC
{

namespace detail
{
    
template<typename T, T start, T stop, T step> struct SeqHelper;

template<typename T, T start, T stop, T step> requires(start + step < stop)
struct SeqHelper<T, start, stop, step>
{
    using Head = Fixed<T,start>;
    using Tail = typename SeqHelper<T, start + step, stop, step>::Type;
    
    using Type = decltype(append(Head{}, Tail{}));
};

template<typename T, T start, T stop, T step> requires(start + step > stop)
struct SeqHelper<T, start, stop, step>
{
    using Type = FixedArray<T, start, stop-1>;
};

template<typename T, T start, T stop, T step> requires(start + step == stop)
struct SeqHelper<T, start, stop, step>
{
    using Type = FixedArray<T, start>;
};

} // namespace detail

/**
 * @brief Alias template for generating a compile-time numeric sequence.
 *
 * Produces a `FixedArray<T,...>` representing a sequence starting at `start`,
 * increasing by `step`, and stopping before/at `stop`, depending on the
 * recursion termination logic defined in `SeqHelper`.
 *
 * @tparam T     Scalar type.
 * @tparam start Starting value.
 * @tparam stop  Limit value used by recursive termination conditions.
 * @tparam step  Step increment (default 1).
 */
template<typename T, T start, T stop, T step=1> 
using Seq  = typename detail::SeqHelper<T, start, stop, step>::Type;

/**
 * @brief Convenience alias for sequences beginning at zero.
 *
 * Equivalent to `Seq<T, 0, stop, step>`.
 *
 * @tparam T     Scalar type.
 * @tparam stop  Bound value for termination.
 * @tparam step  Step increment (default 1).
 */
template<typename T, T stop, T step=1>
using Seq0 = typename detail::SeqHelper<T, 0, stop, step>::Type;

/**
 * @brief Global constexpr instance for easy creation of a compile-time sequence.
 *
 * Usage example:
 * @code
 * auto s = seq<int, 2, 10, 2>; // produces {2,4,6,8}
 * @endcode
 */
template<typename T, T start, T stop, T step=1>
constexpr Seq<T,start,stop, step> seq = {};

/**
 * @brief Global constexpr instance for sequences starting at zero.
 *
 * Usage example:
 * @code
 * auto s = seq0<int, 5>; // produces {0,1,2,3,4}
 * @endcode
 */
template<typename T, T stop, T step=1>
constexpr Seq0<T,stop, step> seq0 = {};

} // namespace BIC

#endif // BIC_SEQ_HPP
