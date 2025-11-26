#ifndef BIC_SEQ_HPP
#define BIC_SEQ_HPP

#include <BIC/FixedArray.hpp>

namespace BIC
{

namespace detail
{
    
template<typename T, T start, T stop, T step, T... values> struct SeqHelper;

template<typename T, T start, T stop, T step, T... values> requires(step > 0 and start + step < stop)
struct SeqHelper<T, start, stop, step, values...>
{
    using Type = typename SeqHelper<T, start + step, stop, step, values..., start>::Type;
};

template<typename T, T start, T stop, T step, T... values> requires(step < 0 and start + step > stop)
struct SeqHelper<T, start, stop, step, values...>
{
    using Type = typename SeqHelper<T, start + step, stop, step, values..., start>::Type;
};

template<typename T, T start, T stop, T step, T... values> requires(step > 0 and start < stop and start + step >= stop)
struct SeqHelper<T, start, stop, step, values...>
{
    using Type = FixedArray<T, values..., start>;
};

template<typename T, T start, T stop, T step, T... values> requires(step < 0 and start > stop and start + step <= stop)
struct SeqHelper<T, start, stop, step, values...>
{
    using Type = FixedArray<T, values..., start>;
};

template<typename T, T start, T stop, T step, T... values> requires(start == stop)
struct SeqHelper<T, start, stop, step, values...>
{
    using Type = FixedArray<T, values...>;
};

} // namespace detail

/**
 * @brief Generate a compile-time numeric sequence of type `T`.
 *
 * Produces a `FixedArray<T,...>` containing a compile-time constant sequence
 * starting at `start`, incrementing by `step`, and terminating according to
 * the rules documented in `SeqHelper`.
 *
 * Example:
 * @code
 * using S = BIC::Seq<int, 2, 10, 3>; // S = {2, 5, 8}
 * @endcode
 *
 * @tparam T     Scalar type.
 * @tparam start Starting value.
 * @tparam stop  Boundary used for recursion termination.
 * @tparam step  Step increment (default 1).
 */
template<typename T, T start, T stop, T step=1> 
using Seq = typename detail::SeqHelper<T, start, stop, step>::Type;

/**
 * @brief Generate a compile-time sequence of indices (`size_t`).
 *
 * Equivalent to `Seq<size_t, start, stop, step>` but shorter and clearer
 * when specifically working with index sequences in templates.
 *
 * Example:
 * @code
 * using I = BIC::IndexSeq<0, 5>; // I = {0,1,2,3,4}
 * @endcode
 *
 * @tparam start First index.
 * @tparam stop  Upper boundary for termination.
 * @tparam step  Step increment (default 1).
 */
template<size_t start, size_t stop, size_t step=1> 
using IndexSeq = typename detail::SeqHelper<size_t, start, stop, step>::Type;

/**
 * @brief Global constexpr instance for compile-time numeric sequences.
 *
 * Example:
 * @code
 * auto s = BIC::seq<int, 2, 10, 2>; // produces {2,4,6,8}
 * @endcode
 */
template<typename T, T start, T stop, T step=1>
constexpr Seq<T,start,stop, step> seq = {};

/**
 * @brief Global constexpr instance for compile-time index sequences.
 *
 * Example:
 * @code
 * auto idx = BIC::indexSeq<0, 5>; // produces {0,1,2,3,4}
 * @endcode
 */
template<size_t start, size_t stop, size_t step=1>
constexpr IndexSeq<start,stop, step> indexSeq = {};

} // namespace BIC

#endif // BIC_SEQ_HPP
