#ifndef BIC_MUT_OR_FIXED_HPP
#define BIC_MUT_OR_FIXED_HPP

#include <BIC/Fixed.hpp>
#include <BIC/IsFixed.hpp>

#include <concepts>

namespace BIC
{

/**
 * @brief Concept that constrains a type to be either a specific type or a Fixed type of that type.
 *
 * The `MutOrFixed` concept is satisfied if and only if the type `VALUE` is either:
 * 1. Exactly the type `T`, or
 * 2. A `BIC::Fixed<T, VALUE>` type whose underlying type matches `T`.
 *
 * This is useful for generic functions or classes that need to accept either
 * runtime values (`T`) or compile-time fixed values (`Fixed<T, VALUE>`),
 * ensuring type safety and compile-time guarantees.
 *
 * @tparam T The base type (usually the mutable type).
 * @tparam VALUE The type or fixed value type to check.
 *
 * @example
 * @code
 * using Size = int;
 * constexpr BIC::Fixed<int, 5> fsize{};
 *
 * static_assert(BIC::MutOrFixed<Size, int>);       // OK
 * static_assert(BIC::MutOrFixed<Size, decltype(fsize)>); // OK
 * static_assert(!BIC::MutOrFixed<Size, double>);   // ERROR: not T or Fixed<T, VALUE>
 * @endcode
 */
template<typename T, typename VALUE>
concept MutOrFixed = std::same_as<T, VALUE> or (IsFixed<VALUE>::value and std::same_as<T, typename Fixed<T, VALUE>::Type>);

} // namespace BIC

#endif // BIC_MUT_OR_FIXED_HPP
