#ifndef BIC_MUTABLE_HPP
#define BIC_MUTABLE_HPP

namespace BIC
{
	
namespace detail
{

template<typename T>
struct MutableTraits
{
    using Type = T;
};

template<typename T, T VALUE> 
struct MutableTraits<Fixed<T,VALUE>>
{
    using Type = T;
};

template<typename T> 
struct MutableTraits<IsFixed<T>>
{
    using Type = bool;
};

} // namespace detail

template<typename T>
using Mutable = typename detail::MutableTraits<T>::Type;
	
} // namespace BIC

#endif // BIC_MUTABLE_HPP
