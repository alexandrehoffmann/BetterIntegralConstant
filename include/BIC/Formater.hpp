#ifndef BIC_FORMATER_HPP
#define BIC_FORMATER_HPP

#include <BIC/Fixed.hpp>
#include <BIC/IsFixed.hpp>

#include <fmt/core.h> 

template<typename T, T value> 
class fmt::formatter<BIC::Fixed<T, value>> 
{ 
public: 
    constexpr auto parse (format_parse_context& ctx) { return ctx.begin(); } 
    
    template <typename Context> 
    constexpr auto format (const BIC::Fixed<T, value>, Context& ctx) const 
    { 
        return format_to(ctx.out(), "{}", value); 
    } 
};

template<typename T> 
class fmt::formatter<BIC::IsFixed<T>> 
{ 
public: 
    constexpr auto parse (format_parse_context& ctx) { return ctx.begin(); } 
    
    template <typename Context> 
    constexpr auto format (const BIC::IsFixed<T>, Context& ctx) const 
    { 
        return format_to(ctx.out(), "{}", BIC::IsFixed<T>::value); 
    } 
};

#endif // BIC_FORMATER_HPP
