#include <fmt/core.h>

int main()
{ 
    ic::Fixed<int, 2> a; 
    ic::Fixed<int, 3> b; 
    
    fmt::print("{}\n", ((a + ic::fixed<long,1>) <= b) and ic::fixed<bool, false>); 
    fmt::print("{}\n", ic::isFixed(((a + ic::fixed<long,1>) <= b) and ic::fixed<bool, false>));
    fmt::print("{}\n", ic::isFixed(ic::isFixed(((a + ic::fixed<long,1>) <= b) and ic::fixed<bool, false>))); 
}
