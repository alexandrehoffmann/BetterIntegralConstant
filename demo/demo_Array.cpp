#include <BIC/Core.hpp>

#include <print>

int main()
{
	std::print("Printing a sequence : {}\n", BIC::seq<size_t,0, 10, 3>);

	std::print("Iterating over a range from Fixed<int,0> to Fixed<int,9>\n");
	BIC::foreach(BIC::fixed<int,0>, BIC::fixed<int,10>, [](const auto i)
	{
		std::print("i = {} is i fixed ? {}\n", i, isFixed(i));
	});
	std::print("Iterating over a reversed range from Fixed<int,9> to Fixed<int,0>\n");
	BIC::foreach(BIC::fixed<int,9>, BIC::fixed<int,0>, BIC::fixed<int,-1>, [](const auto i)
	{
		std::print("i = {} is i fixed ? {}\n", i, isFixed(i));
	});
	std::print("Iterating over the elements of a FixedArray<int,2,4,3,-1,9>\n");
	BIC::foreach(BIC::fixedArray<int,2,4,3,-1,9>, [](const auto i)
	{
		std::print("i = {} is i fixed ? {}\n", i, isFixed(i));
	});
	std::print("Iterating over the elements of a reversed FixedArray<int,2,4,3,-1,9>\n");
	BIC::foreach(reversed(BIC::fixedArray<int,2,4,3,-1,9>), [](const auto i)
	{
		std::print("i = {} is i fixed ? {}\n", i, isFixed(i));
	});
	
	std::print("FixedArray<int,2,4,3,-1,9> contains 9 : {} is fixed ? {}\n", BIC::contains(BIC::fixedArray<int,2,4,3,-1,9>, BIC::fixed<int, 9>), BIC::isFixed(BIC::contains(BIC::fixedArray<int,2,4,3,-1,9>, BIC::fixed<int, 9>)));
	std::print("FixedArray<int,2,4,3,-1,9> contains 9 : {} is fixed ? {}\n", BIC::contains(BIC::fixedArray<int,2,4,3,-1,9>, BIC::fixed<int, 0>), BIC::isFixed(BIC::contains(BIC::fixedArray<int,2,4,3,-1,9>, BIC::fixed<int, 0>)));

	std::print("sub(FixedArray<int, 2,4,3,-1,9>, FixedArray<int, 2,4,3,-1,9>) = {}\n", BIC::substract(BIC::fixedArray<int,2,4,3,-1,9>, BIC::fixedArray<int,2,4,3,-1,9>));
	std::print("sub(FixedArray<int, 2,4,3,-1,9>, FixedArray<int, 2,3,-1>) = {}\n", BIC::substract(BIC::fixedArray<int,2,4,3,-1,9>, BIC::fixedArray<int,2,3,-1>));

	return EXIT_SUCCESS;
}
