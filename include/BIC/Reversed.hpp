#ifndef BIC_REVERSED_HPP
#define BIC_REVERSED_HPP

#include <BIC/FixedArray.hpp>
#include <BIC/Seq.hpp>

namespace BIC
{

namespace detail
{

template<size_t I, typename T, T... VALUES> struct IthValue;

template<size_t I, typename T, T FIRST_VALUE, T... OTHER_VALUES> requires(I==0)
struct IthValue<I,T,FIRST_VALUE,OTHER_VALUES...>
{
    static constexpr T value = FIRST_VALUE;
};

template<size_t I, typename T, T FIRST_VALUE, T... OTHER_VALUES> requires(I!=0)
struct IthValue<I,T,FIRST_VALUE,OTHER_VALUES...>
{
    static constexpr T value = IthValue<I-1, T, OTHER_VALUES...>::value;
};

template<typename Indices, typename T, T... VALUES> struct ReversedHelper;

template<typename T, T... VALUES, size_t... Is>
struct ReversedHelper<FixedIndices<Is...>, T, VALUES...>
{
    using Type = FixedArray<T, (IthValue<sizeof...(VALUES) - 1 - Is, T, VALUES...>::value)...>;
};

} // namespace detail

template<typename T, T... VALUES>
using Reversed = detail::ReversedHelper<Seq<size_t, 0, sizeof...(VALUES)>, T, VALUES...>::Type;

template<typename T, T... VALUES>
constexpr Reversed<T, VALUES...> reversed(FixedArray<T, VALUES...>) { return {}; } 

} // namespace BIC

#endif // BIC_REVERSED_HPP
