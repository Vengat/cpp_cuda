#include "Incr_By_ref.hpp"


void Incr_By_ref::increment(int& x, int& y) {
    ++x;
    ++y;
    
    int tmp = x;
    x = y;
    y = tmp;
}

int main() {
    int x{0}, y{0};
    
    Incr_By_ref instance{};
    
    std::thread t(&Incr_By_ref::increment, &instance, std::ref(x), std::ref(y));
    
    t.join();
    std::cout << " x is " << x << std::endl;
    std::cout << "y is " << y << std::endl;
    
    return 0;
}
