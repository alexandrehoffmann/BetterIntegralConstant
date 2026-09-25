#include <BIC/Core.hpp>

#include <print>

int main()
{
  std::println("Printing a sequence : {}", BIC::seq<size_t, 0, 10, 3>);

  std::println("Iterating over a range from Fixed<int,0> to Fixed<int,9>");
  BIC::foreach(BIC::fixed<int, 0>, BIC::fixed<int, 10>, [](const auto i) { std::print("i = {} is i fixed ? {}", i, isFixed(i)); });
  std::println("Iterating over a reversed range from Fixed<int,9> to Fixed<int,0>");
  BIC::foreach(BIC::fixed<int, 9>, BIC::fixed<int, 0>, BIC::fixed<int, -1>, [](const auto i) { std::print("i = {} is i fixed ? {}", i, isFixed(i)); });
  std::println("Iterating over the elements of a FixedArray<int,2,4,3,-1,9>");
  BIC::foreach(BIC::fixedArray<int, 2, 4, 3, -1, 9>, [](const auto i) { std::print("i = {} is i fixed ? {}", i, isFixed(i)); });
  std::println("Iterating over the elements of a reversed FixedArray<int,2,4,3,-1,9>");
  BIC::foreach(reversed(BIC::fixedArray<int, 2, 4, 3, -1, 9>), [](const auto i) { std::print("i = {} is i fixed ? {}", i, isFixed(i)); });

  std::println("FixedArray<int,2,4,3,-1,9> contains 9 : {} is fixed ? {}", BIC::contains(BIC::fixedArray<int, 2, 4, 3, -1, 9>, BIC::fixed<int, 9>),
               BIC::isFixed(BIC::contains(BIC::fixedArray<int, 2, 4, 3, -1, 9>, BIC::fixed<int, 9>)));
  std::println("FixedArray<int,2,4,3,-1,9> contains 9 : {} is fixed ? {}", BIC::contains(BIC::fixedArray<int, 2, 4, 3, -1, 9>, BIC::fixed<int, 0>),
               BIC::isFixed(BIC::contains(BIC::fixedArray<int, 2, 4, 3, -1, 9>, BIC::fixed<int, 0>)));

  std::println("sub(FixedArray<int, 2,4,3,-1,9>, FixedArray<int, 2,4,3,-1,9>) = {}", BIC::substract(BIC::fixedArray<int, 2, 4, 3, -1, 9>, BIC::fixedArray<int, 2, 4, 3, -1, 9>));
  std::println("sub(FixedArray<int, 2,4,3,-1,9>, FixedArray<int, 2,3,-1>) = {}", BIC::substract(BIC::fixedArray<int, 2, 4, 3, -1, 9>, BIC::fixedArray<int, 2, 3, -1>));

  return EXIT_SUCCESS;
}
