#include <BIC/Core.hpp>

#include <fmt/core.h>

namespace detail
{

template<class Function, typename Tuple, int I>
void enumerateTuple(Function func, const Tuple tuple, const BIC::Fixed<int,I> i)
{
	if constexpr (i != std::tuple_size<Tuple>::value)
	{
		func(i, std::get<i>(tuple));
		enumerateTuple(func, tuple, BIC::next(i));
	}
}

template<class Function, typename Tuple, int I>
void reverseEnumerateTuple(Function func, const Tuple tuple, const BIC::Fixed<int,I> i)
{
	if constexpr (i != -1)
	{
		func(i, std::get<i>(tuple));
		enumerateTuple(func, tuple, BIC::prev(i));
	}
}

} // namespace detail

template<class Function, typename Tuple>
void enumerateTuple(Function func, const Tuple tuple) { return detail::enumerateTuple(func, tuple, BIC::fixed<int,0>); }

template<class Function, typename Tuple>
void reverseEnumerateTuple(Function func, const Tuple tuple) 
{ 
	constexpr int N = std::tuple_size<Tuple>::value;
	
	return detail::reverseEnumerateTuple(func, tuple, BIC::prev(BIC::fixed<int,N>)); 
}

int main()
{
	std::tuple<int, double, char> t(1, -2.9, 'C');
	
	fmt::print("forward enumeration:\n");
	enumerateTuple([](const auto i, const auto ti) -> void
	{
		fmt::print("{}th element of the tuple is {}\n", i, ti);
	}, t);
	fmt::print("backward enumeration:\n");
	reverseEnumerateTuple([](const auto i, const auto ti) -> void
	{
		fmt::print("{}th element of the tuple is {}\n", i, ti);
	}, t);
	
	return EXIT_SUCCESS;
}
