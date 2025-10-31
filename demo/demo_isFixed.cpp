#include <BIC/Core.hpp>

#include <fmt/core.h>

int main()
{ 
    BIC::Fixed<int, 2> a; 
    BIC::Fixed<int, 3> b; 
    
    fmt::print("{}\n", ((a + BIC::fixed<long,1>) <= b) and BIC::fixed<bool, false>); 
    fmt::print("{}\n", BIC::isFixed(((a + BIC::fixed<long,1>) <= b) and BIC::fixed<bool, false>));
    fmt::print("{}\n", BIC::isFixed(BIC::isFixed(((a + BIC::fixed<long,1>) <= b) and BIC::fixed<bool, false>))); 
    
    return EXIT_SUCCESS;
}
