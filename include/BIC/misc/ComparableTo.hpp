#ifndef BIC_MISC_COMPARABLE_TO_HPP
#define BIC_MISC_COMPARABLE_TO_HPP

#include <concepts>

namespace BIC
{

namespace misc 
{ 
	/**
     * @brief Concept ensuring that two types are mutually comparable.
     *
     * @tparam Lhs Left-hand-side type.
     * @tparam Rhs Right-hand-side type.
     *
     * This concept is satisfied if and only if both types support all six
     * comparison operators, and the result of each comparison is convertible
     * to `bool`.
     *
     * Example:
     * @code
     * template<typename T, typename U>
     * requires BIC::misc::ComparableTo<T, U>
     * bool are_equal(const T& a, const U& b) {
     *     return a == b;
     * }
     * @endcode
     */
    template<typename Lhs, typename Rhs> 
    concept ComparableTo = requires(Lhs a, Rhs b) 
    { 
        { a == b } -> std::convertible_to<bool>; 
        { a != b } -> std::convertible_to<bool>; 
        { a < b  } -> std::convertible_to<bool>; 
        { a <= b } -> std::convertible_to<bool>; 
        { a > b  } -> std::convertible_to<bool>; 
        { a >= b } -> std::convertible_to<bool>; 
    }; 
} // namespace misc

} // namespace ic

#endif // BIC_MISC_COMPARABLE_TO_HPP
