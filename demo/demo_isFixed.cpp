#include <BIC/Core.hpp>

#include <print>

int main()
{ 
    BIC::Fixed<int, 2> a; 
    BIC::Fixed<int, 3> b; 
    
    std::print("{}\n", ((a + BIC::fixed<long,1>) <= b) and BIC::fixed<bool, false>); 
    std::print("{}\n", BIC::isFixed(((a + BIC::fixed<long,1>) <= b) and BIC::fixed<bool, false>));
    std::print("{}\n", BIC::isFixed(BIC::isFixed(((a + BIC::fixed<long,1>) <= b) and BIC::fixed<bool, false>))); 
    
    return EXIT_SUCCESS;
}
