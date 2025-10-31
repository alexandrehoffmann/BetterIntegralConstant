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
 * The `MutOrFixed` concept is satisfied if and only if the type `Type` is either:
 * 1. Exactly the type `RefType`, or
 * 2. A `BIC::Fixed` type whose underlying type matches `RefType`.
 *
 * This is useful for generic functions or classes that need to accept either
 * runtime values (`RefType`) or compile-time fixed values (`Fixed<RefType, VALUE>`),
 * ensuring type safety and compile-time guarantees.
 *
 * @tparam RefType The reference type (usually a native type).
 * @tparam Type The type or fixed value type to check.
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
template<typename RefType, typename Type>
concept MutOrFixed = std::same_as<RefType, Type> or (IsFixed<Type>::value and std::same_as<RefType, typename Type::Type>);

} // namespace BIC

#endif // BIC_MUT_OR_FIXED_HPP
