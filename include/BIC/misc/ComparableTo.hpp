#ifndef BIC_MISC_COMPARABLE_TO_HPP
#define BIC_MISC_COMPARABLE_TO_HPP

namespace BIC
{

namespace misc 
{ 
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
