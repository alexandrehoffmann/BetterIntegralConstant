# Better Integral Constant (BIC)

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
