#include <BIC/Core.hpp>

#include <fmt/core.h>
#include <fmt/ranges.h>

int main()
{
    fmt::print("Printing a sequence : {}\n", fmt::join(BIC::seq<size_t,0, 10, 3>, ", "));
	
	fmt::print("Iterating over a range from Fixed<int,0> to Fixed<int,9>\n");
    BIC::foreach(BIC::fixed<int,0>, BIC::fixed<int,10>, [](const auto i)
    {
        fmt::print("i = {} is i fixed ? {}\n", i, isFixed(i));
    });
	fmt::print("Iterating over a reversed range from Fixed<int,9> to Fixed<int,0>\n");
    BIC::foreach(BIC::fixed<int,9>, BIC::fixed<int,0>, BIC::fixed<int,-1>, [](const auto i)
    {
        fmt::print("i = {} is i fixed ? {}\n", i, isFixed(i));
    });
	fmt::print("Iterating over the elements of a FixedArray<int,2,4,3,-1,9>\n");
    BIC::foreach(BIC::fixedArray<int,2,4,3,-1,9>, [](const auto i)
    {
        fmt::print("i = {} is i fixed ? {}\n", i, isFixed(i));
    });
}
