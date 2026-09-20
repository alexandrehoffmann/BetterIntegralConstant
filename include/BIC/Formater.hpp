#ifndef BIC_FORMATER_HPP
#define BIC_FORMATER_HPP

#include <BIC/Fixed.hpp>
#include <BIC/FixedArray.hpp>
#include <BIC/IsFixed.hpp>

#include <format> 

template<typename T, T value> 
class std::formatter<BIC::Fixed<T, value>> 
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
class std::formatter<BIC::IsFixed<T>> 
{ 
public: 
    constexpr auto parse (format_parse_context& ctx) { return ctx.begin(); } 
    
    template <typename Context> 
    constexpr auto format (const BIC::IsFixed<T>, Context& ctx) const 
    { 
        return format_to(ctx.out(), "{}", BIC::IsFixed<T>::value); 
    } 
};

template<typename T, T... VALUES>
class std::formatter<BIC::FixedArray<T, VALUES...>>
{
public: 
	constexpr auto parse (format_parse_context& ctx) { return ctx.begin(); } 
    
	template <typename Context> 
    constexpr auto format (const BIC::FixedArray<T, VALUES...>, Context& ctx) const 
    { 
        return format_to(ctx.out(), "{}", BIC::FixedArray<T, VALUES...>::values); 
    } 
    	
};

#endif // BIC_FORMATER_HPP
