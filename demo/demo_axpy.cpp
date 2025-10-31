#include <vector>
#include <fmt/ranges.h>

template<typename Alpha, typename Scalar, typename Size>
void axpy(const Alpha alpha, const Scalar* x, const Size N, Scalar* y)
{
    for (ic::Mutable<Size> i=0; i!=N; ++i)
    {
        y[i] = alpha*x[i];
    }
}

int main()
{
	constexpr size_t N = 20;
	
	std::vector<double, N> x(N, 1);
	std::vector<double, N> y(N, 2);
	
	// axpy without BIC::fixed, the if axpy is not inlined
	// the compiler will generate a for loop
	axpy(1, x.data(), 10, y.data()); 
	
	fmt::print("y = {}\n", fmt::join(y, ", "));
	// axpy with BIC::fixed, the if axpy is not inlined
	// the compiler doen't need to generate a loop
	axpy(BIC::fixed<double,1.>, x.data(), BIC::fixed<size_t, 10>, y.data());
}
