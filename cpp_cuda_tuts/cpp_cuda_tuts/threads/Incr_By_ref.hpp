#ifndef Incr_By_Ref_hpp
#define Incr_By_Ref_hpp

#include <string>
#include <iostream>
#include <thread>
#include <functional>


class Incr_By_ref {
public:
    
    void increment(int& x, int& y);
    
};
#endif
