#ifndef BIC_MAYBE_FIXED_HPP
#define BIC_MAYBE_FIXED_HPP

#include <BIC/Mutable.hpp>

#include <concepts>

namespace BIC
{

/**
 * @brief Checks whether `MaybeFixed` represents a value of type `T`,
 *        either directly or as a compile-time fixed value.
 *
 * `MaybeFixed` may be:
 * - `T` itself, or
 * - `Fixed<T, VALUE>`, whose mutable/underlying type is `T`.
 *
 * `Mutable<MaybeFixed>` extracts the underlying type, allowing code to
 * accept both runtime values and `Fixed` compile-time values through the
 * same template interface.
 *
 * @tparam MaybeFixed Type that may be a regular type or a `Fixed` type.
 * @tparam T          Expected underlying value type.
 *
 * @code
 * static_assert(CMaybeFixed<int, int>);
 * static_assert(CMaybeFixed<Fixed<int, 42>, int>);
 *
 * static_assert(!CMaybeFixed<Fixed<int, 42>, double>);
 * @endcode
 */
template<typename MaybeFixed, typename T>
concept CMaybeFixed = std::same_as<Mutable<MaybeFixed>, T>;

} // namespace BIC

#endif // BIC_MAYBE_FIXED_HPP
