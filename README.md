# Better Integral Constant (BIC)

## Fixed type

A header-only library providing a `Fixed` type which represents a compile-time fixed constant (similar to integral constant).
A `Fixed` can be implicitly converted to the underlying type and supports arithmetic, logical and comparaison operators.
Obviously arithmetic operations between two `Fixed` returns a `Fixed`.

```cpp
 BIC::Fixed<int, 2> a; 
 BIC::Fixed<int, 3> b; 
    
 static_assert( ((a + BIC::fixed<long,1>) <= b) and BIC::fixed<bool, false> == false); 
 static_assert( BIC::isFixed(((a + BIC::fixed<long,1>) <= b) and BIC::fixed<bool, false>));
 static_assert( BIC::isFixed(BIC::isFixed(((a + BIC::fixed<long,1>) <= b) and BIC::fixed<bool, false>))); 
```
`BIC` allows for easy compile time recursion:
```cpp
namespace detail
{
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
void reverseEnumerateTuple(Function func, const Tuple tuple) 
{ 
	constexpr int N = std::tuple_size<Tuple>::value;
	return detail::reverseEnumerateTuple(func, tuple, BIC::prev(BIC::fixed<int,N>)); 
}

std::tuple<int, double, char> t(1, -2.9, 'C');
reverseEnumerateTuple([](const auto i, const auto ti) -> void
{
	fmt::print("{}th element of the tuple is {}\n", i, ti);
}, t);
```

`BIC` Is inteneded to help the compiler optimizing kernels

```cpp
template<typename Alpha, typename Scalar, typename Size>
void axpy(const Alpha alpha, const Scalar* x, const Size N, Scalar* y)
{
  // Size may be a BIC::Fixed so we iterate with a 
  // BIC::Mutable<Size> 
  for (BIC::Mutable<Size> i=0; i!=N; ++i)
  {
    y[i] += alpha*x[i];
  }
}
```
Our kernel can be called with either native types or `BIC::Fixed`:
```cpp
	constexpr size_t N = 20;
	
	std::vector<double> x(N, 1);
	std::vector<double> y(N, 2);
	
	axpy(1, x.data(), N, y.data()); 
	axpy(BIC::fixed<double,1.>, x.data(), BIC::fixed<size_t, N>, y.data());
```

## FixedArray and Sequences

Basic usage:

```cpp
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
	fmt::print("Iterating over the elements of a reversed FixedArray<int,2,4,3,-1,9>\n");
    BIC::foreach(reversed(BIC::fixedArray<int,2,4,3,-1,9>), [](const auto i)
    {
        fmt::print("i = {} is i fixed ? {}\n", i, isFixed(i));
    });
```

Concatenation:
Here we compute the Ith lagrange polynomials by concatenating two `BIC::Seq`, one from O,to I and another from I+1 to N.

```cpp
template<int I, int N>
double getLagrangePolynomial(const double t, const BIC::Fixed<int, I> i, const BIC::Fixed<int, N> /* n */) const 
{ 
	return getLagrangePolynomial(t, i, BIC::cat(BIC::seq<int, 0u, I>, BIC::seq<int, I+1, N>)); 
}

template<int I, int... Js> 
double getLagrangePolynomial(const double t, const BIC::Fixed<int, I> i, const BIC::FixedArray<int, Js...> /* js */) const 
{ 
	return ((double(t - Js) / double(i - Js)) * ...); 
}
```
